

#include <Tracko/Screens/CustomizeYourTrain.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{
namespace Screens
{


CustomizeYourTrain::CustomizeYourTrain(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Screens::Base(Tracko::Screens::CustomizeYourTrain::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , level_select_element()
   , on_menu_choice_callback_func()
   , on_menu_choice_callback_func_user_data(nullptr)
   , initialized(false)
{
}


CustomizeYourTrain::~CustomizeYourTrain()
{
}


void CustomizeYourTrain::set_on_menu_choice_callback_func(std::function<void(Tracko::Screens::CustomizeYourTrain*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void CustomizeYourTrain::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


std::function<void(Tracko::Screens::CustomizeYourTrain*, void*)> CustomizeYourTrain::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* CustomizeYourTrain::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


AllegroFlare::Elements::LevelSelect &CustomizeYourTrain::get_level_select_element_ref()
{
   return level_select_element;
}


void CustomizeYourTrain::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void CustomizeYourTrain::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void CustomizeYourTrain::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void CustomizeYourTrain::set_levels_list(std::vector<std::pair<std::string, std::string>> levels_list)
{
   level_select_element.set_levels_list(levels_list);
   return;
}

void CustomizeYourTrain::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::initialize: error: guard \"font_bin\" not met");
   }
   initialized = true;

   level_select_element.set_event_emitter(event_emitter);
   level_select_element.set_font_bin(font_bin);
   level_select_element.set_on_menu_choice_callback_func([this](AllegroFlare::Elements::LevelSelect*, void*){
      if (on_menu_choice_callback_func)
         on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   });

   return;
}

void CustomizeYourTrain::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::on_activate: error: guard \"initialized\" not met");
   }
   // TODO: emit_event_to_update_input_hints_bar();
   // TODO: emit_show_and_size_input_hints_bar_event();

   // TODO: Test the calling and error message response here in this "submit_on_activate_if_empty" block
   bool submit_on_activate_if_empty = true;
   if (submit_on_activate_if_empty && level_select_element.list_is_empty())
   {
      if (!on_menu_choice_callback_func)
      {
         AllegroFlare::Logger::throw_error(
            "Tracko::Screens::CustomizeYourTrain",
            "\"submit_on_activate_if_empty\" is set to true, thus expecting an \"on_menu_choice_callback_func\" "
               " to be present but it is not."
         );
      }

      // TODO: Add boolean option to supress this message
      AllegroFlare::Logger::info_from(
         "Tracko::Screens::CustomizeYourTrain",
         "\"submit_on_activate_if_empty\" is true, so now calling \"on_menu_choice_callback_func\"."
      );

      on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   }
   return;
}

void CustomizeYourTrain::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::on_deactivate: error: guard \"initialized\" not met");
   }
   // TODO: emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void CustomizeYourTrain::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::update: error: guard \"initialized\" not met");
   }
   return;
}

void CustomizeYourTrain::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::render: error: guard \"initialized\" not met");
   }
   level_select_element.render();
   return;
}

void CustomizeYourTrain::activate_selected_menu_option()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::activate_selected_menu_option]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::activate_selected_menu_option: error: guard \"initialized\" not met");
   }
   level_select_element.activate_selected_menu_option();
   return;
}

std::string CustomizeYourTrain::infer_current_menu_option_value()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::infer_current_menu_option_value]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::infer_current_menu_option_value: error: guard \"initialized\" not met");
   }
   return level_select_element.infer_current_menu_option_value();
}

void CustomizeYourTrain::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::primary_timer_func: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void CustomizeYourTrain::joy_button_down_func(ALLEGRO_EVENT* ev)
{
   activate_selected_menu_option();
   return;
}

void CustomizeYourTrain::joy_axis_func(ALLEGRO_EVENT* ev)
{
   static float axis_x = 0;
   static float axis_y = 0;

   int stick = ev->joystick.stick;
   int axis = ev->joystick.axis;
   float pos = ev->joystick.pos;

   float min_stick_break_threshold = 0.4;

   switch (stick)
   {
      case 0: { // The primary joystick, on the left
        if (axis == 0) // horizontal axis
        {
           if (axis_x < min_stick_break_threshold && pos >= min_stick_break_threshold) 
               level_select_element.move_cursor_right();
           if (axis_x > -min_stick_break_threshold && pos <= -min_stick_break_threshold) 
               level_select_element.move_cursor_left();
           axis_x = pos;
        }
        else if (axis == 1) // vertical axis
        {
           if (axis_y < min_stick_break_threshold && pos >= min_stick_break_threshold) 
               level_select_element.move_cursor_down();
           if (axis_y > -min_stick_break_threshold && pos <= -min_stick_break_threshold) 
               level_select_element.move_cursor_up();
           axis_y = pos;
        }
      } break;

      case 1: { // The secondary joystick, on the right
      } break;

      case 2: { // The hat, on the left
      } break;
   }

   return;
}

void CustomizeYourTrain::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void CustomizeYourTrain::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   // TODO: Confirm usage of VirtualControllers::GenericController

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP: {
         level_select_element.move_cursor_up();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN: {
         level_select_element.move_cursor_down();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT: {
         level_select_element.move_cursor_left();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT: {
         level_select_element.move_cursor_right();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_MENU:
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_A: {
         activate_selected_menu_option();
      } break;
   }

   return;
}

void CustomizeYourTrain::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CustomizeYourTrain::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CustomizeYourTrain::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}


} // namespace Screens
} // namespace Tracko


