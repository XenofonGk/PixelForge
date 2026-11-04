#include "History.h"
#include "Common.h"
#include <stdexcept>
#include <utility>

History::History(Image first) {
    // TODO Day 17: move first into a new shared_ptr and store it in now. Use std::make_shared.
    NOT_IMPLEMENTED();
}
void History::commit(Image next) {
    // TODO Day 17: push now onto undoStack, store next in now, and clear redoStack.
    NOT_IMPLEMENTED();
}
bool History::undo() {
    // TODO Day 17: return false if undoStack is empty. Otherwise push now onto redoStack and pop the old image into now.
    NOT_IMPLEMENTED();
}
bool History::redo() {
    // TODO Day 17: the mirror image of undo().
    NOT_IMPLEMENTED();
}
std::unique_ptr<Filter> makeFilter(const std::string& name) {
    // TODO Day 17: return std::make_unique of the right class, or throw std::invalid_argument.
    NOT_IMPLEMENTED();
}
