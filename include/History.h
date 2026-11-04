#ifndef FORGE_HISTORY_H
#define FORGE_HISTORY_H
// Day 17: smart pointers. History shares images with shared_ptr;
// makeFilter hands back sole ownership with unique_ptr.
// Notes: F-MemoryModel/smart-pointers
#include "FilterClasses.h"
#include "Stack.h"
#include <memory>
#include <string>

using ImagePtr = std::shared_ptr<const Image>;

class History {
    Stack<ImagePtr> undoStack;
    Stack<ImagePtr> redoStack;
    ImagePtr now;
public:
    explicit History(Image first);
    void commit(Image next);    // old image goes on undoStack; redoStack is cleared
    bool undo();                // false when there is nothing to undo
    bool redo();                // false when there is nothing to redo
    ImagePtr current() const { return now; }
    int undoCount() const { return undoStack.size(); }
    int redoCount() const { return redoStack.size(); }
};

// Returns a filter by name; throws std::invalid_argument for an unknown name.
std::unique_ptr<Filter> makeFilter(const std::string& name);

#endif
