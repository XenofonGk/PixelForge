#include "Filters.h"
#include "Common.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

int luma(Pixel p) { return (red(p) * 299 + green(p) * 587 + blue(p) * 114) / 1000; }

void invert(Image& img) {
    std::transform(img.begin(), img.end(), img.begin(), invertRGB);
}
void grayscale(Image& img) {
    std::transform(img.begin(), img.end(), img.begin(),[](Pixel p){
        int l = luma(p);
       return pack( l,l,l,alpha(p)); } );
}
void threshold(Image& img, int level) {

    std::transform(img.begin(),img.end(), img.begin(), [level] (Pixel p) {
        int l = luma(p);
    if (l < level){
        return pack(0,0,0, alpha(p));
    } 
        return pack(255,255,255,alpha(p));
    });
}
bool isGrayscale(const Image& img) {
    // TODO Day 8: use std::all_of.
    return std::all_of(img.begin(), img.end(), [] (Pixel p) {return red(p) == green(p) && green(p) == blue(p); });

}

// ---- Day 9 ----
Pixel adjustBrightness(Pixel p, int amount) {
    return pack(clampByte(red(p) + amount), clampByte(green(p) + amount), clampByte(blue(p) + amount), alpha(p));
}
PixelFn brightness(int amount) {
   return std::bind(adjustBrightness, std::placeholders::_1, amount);
}
PixelFn tint(double r, double g, double b) {
    return [r, g, b] (Pixel p) {
    return pack(clampByte(red(p) * r),
    clampByte(green(p) * g),
    clampByte(blue(p) * b),
    alpha(p));
    };
}
void applyFn(Image& img, const PixelFn& fn) {
    std::transform(img.begin(), img.end(), img.begin(),fn);
}
void applyAll(Image& img, const std::vector<PixelFn>& steps) {
    for (const PixelFn& fn : steps){
    std::transform(img.begin(), img.end(), img.begin(),fn);
    }
}
void countInto(int& counter, Pixel p, int level) {
    if (luma(p) >= level) 
    counter++;
}
int countWithRef(const Image& img, int level) {
    int counter = 0;
    std::for_each(img.begin(), img.end(),  std::bind(countInto, std::ref(counter), std::placeholders::_1, level));
    return counter;
}

Histogram histogram(const Image& img) {
    Histogram hist{};

    std::for_each(img.begin(), img.end(), [&hist] (Pixel p ) { 
        hist[luma(p)]++;
    } );
    return hist;
}
int countBright(const Image& img, int level) {
    return std::count_if(img.begin(), img.end(), [level] (Pixel p) {
       return  luma(p) >= level;
        
    });
}
double meanLuma(const Histogram& hist) {
    
    int count = std::accumulate(hist.begin(), hist.end(), 0);
    if (count == 0) {
        return 0;
    }
    double sum = 0;
    for (int i = 0; i < 256; i++){
        sum += i * hist[i];
    }
    return sum / count;
}
std::vector<Pixel> selectBright(const Image& img, int level) {
    // TODO Day 10: use std::copy_if with std::back_inserter.
    std::vector<Pixel> result{};

    std::copy_if(img.begin(), img.end(), std::back_inserter(result), [level] (Pixel p) {
       return  luma(p) >= level;
        
    });
    return result;
}

// ---- Day 12 ----
std::array<int, 256> cumulative(const Histogram& hist) {
    std::array<int, 256> cdf{};
    std::partial_sum(hist.begin(),hist.end(), cdf.begin());
    return cdf;
}
void equalize(Image& img) {
    std::array<int, 256> cdf = cumulative(histogram(img));

    int cdfMin = 0;
    for (int i = 0; i < 256; i++){
        if (cdf[i] != 0){
            cdfMin = cdf[i];
            break;
        }
    }
    int pixels = img.width() * img.height();

    int bottom = pixels - cdfMin;
    if (bottom == 0){
        return;
    }
    std::transform(img.begin(), img.end(),img.begin(), [&cdf, cdfMin, bottom] (Pixel p) {
        return pack((cdf[red(p)] - cdfMin) * 255 / bottom,(cdf[green(p)] - cdfMin) * 255 / bottom,(cdf[blue(p)] - cdfMin) * 255 / bottom, alpha(p));
    });
    }


// ---- Day 13 ----
int weightedSum(const int* weights, const int* samples, int n) {
    return std::inner_product(weights, weights + n, samples, 0);
}
Image convolve(const Image& src, const int (*kernel)[3], int divisor) {
    Image out(src.width(),src.height());
    for (int y = 0; y < src.height();y++){
        for (int x = 0; x < src.width(); x++){
        int sumR{};
        int sumG{};
        int sumB{};
        for (int ky = 0; ky < 3; ky++){
            int ny = FORGE_CLAMP(y + ky -1, 0,src.height() -1 );
            int reds[3];
            int greens[3];
            int blues[3];
            for (int kx = 0; kx < 3; kx++){
                int nx = FORGE_CLAMP(x + kx -1, 0,src.width() -1 );
                reds[kx] = red(src.at(nx, ny));
                greens[kx] = green(src.at(nx, ny));
                blues[kx] = blue(src.at(nx,ny));
            }
            sumR += weightedSum(kernel[ky], reds,3);
            sumG += weightedSum(kernel[ky], greens, 3);
            sumB += weightedSum(kernel[ky], blues, 3);
        }
        out.at(x,y) = pack(clampByte(sumR / divisor), clampByte(sumG / divisor), clampByte(sumB / divisor), alpha(src.at(x,y)));
        }
    }
        return out;
}
Image blur(const Image& src) {
    const int kernel[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
    return convolve(src, kernel, 16);
}
Image sharpen(const Image& src) {
    const int kernel[3][3] = {{0,-1,0},{-1,5,-1},{0,-1,0}};
    return convolve(src, kernel, 1);
}

// ---- Day 14 ----
int medianOf(std::array<int, 9> values) {
    std::sort(values.begin(), values.end());
    return values[4];
}
Image medianFilter(const Image& src) {
    Image out(src.width(),src.height());
    for (int y = 0; y < src.height();y++){
        for (int x = 0; x < src.width(); x++){
            std::array<int, 9> reds;
            std::array<int, 9> greens;
            std::array<int, 9> blues;
            int i = 0;
            for (int ky = 0; ky < 3; ky++){
                int ny = FORGE_CLAMP(y + ky -1, 0,src.height() -1 );
                for (int kx = 0; kx < 3; kx++){
                    int nx = FORGE_CLAMP(x + kx -1, 0,src.width() -1 );
                reds[i] = red(src.at(nx, ny));
                greens[i] = green(src.at(nx, ny));
                blues[i] = blue(src.at(nx,ny));
                i++;
            }
            }
             out.at(x,y) = pack(medianOf(reds),medianOf(greens), medianOf(blues), alpha(src.at(x,y)));
        }
    }
    return out;
}
std::vector<int> topLumas(const Image& img, int n) {
   std::vector<int> lumas{};
    for (Pixel p : img){
        lumas.push_back(luma(p));
        }
         std::sort(lumas.begin(), lumas.end(), std::greater<int>());
         if (n < lumas.size()){
        lumas.resize(n);
    }
    return lumas;
}

