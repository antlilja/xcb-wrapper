// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <xcb_wrapper/xcb_wrapper.hpp>

class window {
private:
    static constexpr auto c_event_mask = xcbw::event_mask_attrib(
        xcbw::event_mask_bits::e_exposure, xcbw::event_mask_bits::e_structure_notify,
        xcbw::event_mask_bits::e_enter_window, xcbw::event_mask_bits::e_leave_window,
        xcbw::event_mask_bits::e_key_press, xcbw::event_mask_bits::e_key_release,
        xcbw::event_mask_bits::e_button_press, xcbw::event_mask_bits::e_button_release,
        xcbw::event_mask_bits::e_pointer_motion, xcbw::event_mask_bits::e_focus_change);

private:
    void process_event(const xcbw::generic_event_t& next, const xcbw::generic_event_t& curr,
                       const xcbw::generic_event_t& prev) {

        using namespace xcbw;
        switch (curr.get_event_type()) {
            case event_type_t::e_client_message: {
                const auto& client_message = static_cast<const client_message_event_t&>(curr);
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
        : m_window(m_instance, xcbw::window_class_t::e_input_output, m_instance.get_root(), {},
                   {960, 540}, 1, m_instance.get_root_visual(),
                   xcbw::make_window_attributes(
                       xcbw::back_pixel_attrib(m_instance.get_black_pixel()), c_event_mask)),
          m_delete_window_atom(m_instance, false, "WM_DELETE_WINDOW"), m_open(true) {

        using namespace xcbw;
        // Delete window setup
        {
            intern_atom_t i_atom(m_instance, true, "WM_PROTOCOLS");
            m_window.change_property(m_instance, property_mode_t::e_replace, i_atom.get_atom(),
                                     atom_type_t::e_atom, m_delete_window_atom.get_atom());
        }

        // Setting window title
        m_window.change_property(m_instance, property_mode_t::e_replace, atom_type_t::e_wm_name,
                                 atom_type_t::e_string, "Testing window");

        m_window.map(m_instance);
        m_instance.flush();
    }

    ~window() { m_window.destroy(m_instance); }

    bool is_open() const { return m_open; }

    void poll_for_events() {
        if (auto curr = m_instance.poll_for_events(); !curr.is_null()) {
            xcbw::generic_event_t prev(nullptr);

            auto next = m_instance.poll_for_events();
            while (!next.is_null()) {
                process_event(next, curr, prev);
                prev = std::move(curr);
                curr = std::move(next);
                next = m_instance.poll_for_events();
            }
            process_event(next, curr, prev);
        }
    }

private:
    xcbw::instance_t m_instance;
    xcbw::window_t m_window;
    xcbw::intern_atom_t m_delete_window_atom;

    bool m_open;
};

int main() {
    window win;

    while (win.is_open()) {
        win.poll_for_events();
    }
}