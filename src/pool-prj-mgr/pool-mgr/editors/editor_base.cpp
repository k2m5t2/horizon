#include "editor_base.hpp"
#include "util/file_version.hpp"

namespace horizon {
unsigned int PoolEditorBase::get_required_version() const
{
    return get_version().get_app();
}

void PoolEditorBase::label_make_item_link(Gtk::Label &la, ObjectType type)
{
    la.set_track_visited_links(false);
    auto menu = Gtk::manage(new Gtk::Menu);
    menu->attach_to_widget(la);
    auto it = Gtk::manage(new Gtk::MenuItem("Edit"));
    menu->append(*it);
    it->show();
    it->signal_activate().connect([&la, type, this] {
        auto uri = la.get_current_uri();
        if (!uri.size())
            return;
        s_signal_open_item.emit(type, UUID(uri));
    });
    la.signal_button_press_event().connect(
            [&la, menu](GdkEventButton *ev) {
                if (!gdk_event_triggers_context_menu((GdkEvent *)ev))
                    return false;
                int start, end;
                if (la.get_selection_bounds(start, end))
                    return false;
                if (!la.get_current_uri().size())
                    return false;
                menu->popup_at_pointer((GdkEvent *)ev);
                return true;
            },
            false);
    la.signal_activate_link().connect(
            [this, type](const std::string &url) {
                s_signal_goto.emit(type, UUID(url));
                return true;
            },
            false);
}

} // namespace horizon
