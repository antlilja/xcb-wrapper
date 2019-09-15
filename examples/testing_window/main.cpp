#include <xcb_wrapper/xcb_wrapper.hpp>

const auto c_event_mask = xcbw::event_mask(
    xcbw::event_mask_bits::e_exposure, xcbw::event_mask_bits::e_structure_notify,
    xcbw::event_mask_bits::e_enter_window, xcbw::event_mask_bits::e_leave_window,
    xcbw::event_mask_bits::e_key_press, xcbw::event_mask_bits::e_key_release,
    xcbw::event_mask_bits::e_button_press, xcbw::event_mask_bits::e_button_release,
    xcbw::event_mask_bits::e_pointer_motion, xcbw::event_mask_bits::e_focus_change);

class window {
private:
    void process_event(const xcbw::generic_event& next, const xcbw::generic_event& curr,
                       const xcbw::generic_event& prev) {

        using namespace xcbw;
        switch (curr.get_event_type()) {
            case event_type::e_client_message: {
                const auto& client_message = static_cast<const client_message_event&>(curr);
                const auto atom = static_cast<uint32_t>(m_delete_window_atom.get_atom());
                if (client_message.get_data().data32[0] == atom) {
                    m_open = false;
                }
                break;
            }
            default: break;
        }
    }

public:
    window()
        : m_connection(nullptr, nullptr), m_screen(m_connection),
          m_window(m_connection, xcbw::window_class::input_output, m_screen.get_root(), {},
                   {960, 540}, 1, m_screen.get_root_visual(),
                   xcbw::make_window_attributes(xcbw::back_pixel(m_screen.get_black_pixel()),
                                                c_event_mask)),
          m_delete_window_atom(m_connection, false, "WM_DELETE_WINDOW"), m_open(true) {

        using namespace xcbw;
        // Delete window setup
        {
            intern_atom i_atom(m_connection, true, "WM_PROTOCOLS");
            m_window.change_property(m_connection, prop_mode::replace, i_atom.get_atom(),
                                     atom_type::e_atom, m_delete_window_atom.get_atom());
        }

        // Setting window title
        m_window.change_property(m_connection, prop_mode::replace, atom_type::e_wm_name,
                                 atom_type::e_string, "Testing window");

        m_window.map(m_connection);
        m_connection.flush();
    }

    ~window() { m_window.destroy(m_connection); }

    bool is_open() const { return m_open; }

    void poll_for_events() {
        if (auto curr = m_connection.poll_for_events(); !curr.is_null()) {
            xcbw::generic_event prev(nullptr);

            auto next = m_connection.poll_for_events();
            while (!next.is_null()) {
                process_event(next, curr, prev);
                prev = std::move(curr);
                curr = std::move(next);
                next = m_connection.poll_for_events();
            }
            process_event(next, curr, prev);
        }
    }

private:
    xcbw::connection m_connection;
    xcbw::screen m_screen;
    xcbw::window m_window;
    xcbw::intern_atom m_delete_window_atom;

    bool m_open;
};

int main() {
    window win;

    while (win.is_open()) {
        win.poll_for_events();
    }
}