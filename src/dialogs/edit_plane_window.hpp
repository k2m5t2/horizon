#pragma once
#include "tool_window.hpp"
#include "util/uuid.hpp"

namespace horizon {

class ToolDataEditPlane : public ToolDataWindow {
public:
    bool pick_net = false;
};

class EditPlaneWindow : public ToolWindow {
public:
    EditPlaneWindow(Gtk::Window *parent, ImpInterface *intf, class Plane &p, class Board &brd);
    void set_net(const UUID &uu);

private:
    void handle_event(ToolDataWindow::Event ev) override;
    Gtk::ToggleButton *pick_button = nullptr;
    class NetButton *net_button = nullptr;

    class Plane &plane;
    const UUID plane_uuid;
    class Board &brd;
    class Polygon &poly;
};
} // namespace horizon
