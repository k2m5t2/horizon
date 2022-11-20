#pragma once
#include <string>
#include <memory>
#include <deque>
#include "changeable.hpp"

namespace horizon {
class HistoryManager : public Changeable {
public:
    class HistoryItem {
    public:
        HistoryItem(const std::string &c) : comment(c)
        {
        }
        const std::string comment;
        virtual ~HistoryItem() = default;
    };

    const HistoryItem &undo();
    const HistoryItem &redo();
    const HistoryItem &get_current();

    bool can_undo() const;
    bool can_redo() const;

    const std::string &get_undo_comment() const;
    const std::string &get_redo_comment() const;

    void set_history_max(unsigned int m);

    void push(std::unique_ptr<const HistoryItem> it);
    void clear();

private:
    std::shared_ptr<const HistoryItem> history_current;
    std::deque<std::shared_ptr<const HistoryItem>> undo_stack;
    std::deque<std::shared_ptr<const HistoryItem>> redo_stack;

    unsigned int history_max = 50;
    void trim();
};
} // namespace horizon
