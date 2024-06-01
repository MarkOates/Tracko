

#include <Tracko/Gameplay/Screen.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <Tracko/BoardRenderer.hpp>
#include <Tracko/GameConfigurations/Main.hpp>
#include <Tracko/Gameplay/Level.hpp>
#include <Tracko/PieceRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tracko
{
namespace Gameplay
{


Screen::Screen()
   : AllegroFlare::Screens::Gameplay()
   , data_folder_path(DEFAULT_DATA_FOLDER_PATH)
   , asset_studio_database(nullptr)
   , event_emitter(nullptr)
   , bitmap_bin(nullptr)
   , font_bin(nullptr)
   , model_bin(nullptr)
   , game_configuration(nullptr)
   , current_level_identifier("[unset-current_level]")
   , current_level(nullptr)
   , camera({})
   , current_board(nullptr)
   , current_board_start_tile({})
   , current_board_start_tile_start_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_UNDEF)
   , current_board_placement({})
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_data_folder_path(std::string data_folder_path)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_data_folder_path]: error: guard \"get_initialized()\" not met.");
   this->data_folder_path = data_folder_path;
}


void Screen::set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_asset_studio_database]: error: guard \"get_initialized()\" not met.");
   this->asset_studio_database = asset_studio_database;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_model_bin]: error: guard \"get_initialized()\" not met.");
   this->model_bin = model_bin;
}


void Screen::set_game_configuration(Tracko::GameConfigurations::Main* game_configuration)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_game_configuration]: error: guard \"get_initialized()\" not met.");
   this->game_configuration = game_configuration;
}


std::string Screen::get_data_folder_path() const
{
   return data_folder_path;
}


Tracko::GameConfigurations::Main* Screen::get_game_configuration() const
{
   return game_configuration;
}


bool Screen::get_initialized() const
{
   return initialized;
}


AllegroFlare::AssetStudio::Database* &Screen::get_asset_studio_database_ref()
{
   return asset_studio_database;
}


void Screen::load_level_by_identifier(std::string level_identifier)
{
   if (!(game_configuration))
   {
      std::stringstream error_message;
      error_message << "[Screen::load_level_by_identifier]: error: guard \"game_configuration\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::load_level_by_identifier: error: guard \"game_configuration\" not met");
   }
   // Destroy the current level
   if (current_level)
   {
      // TODO: Shutdown current level
      delete current_level;
   }

   // Reset the camera position
   camera.position = { 0, 0 };

   // DEVELOPMENT: build random board
   if (current_board) delete current_board;

   current_board_start_tile = { 0, 1 };
   current_board_start_tile_start_connecting_position = Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT;
   current_board = new Tracko::Board;
   current_board->resize(7, 5);
   current_board->fill_with_random_types();
   current_board->set_random_tile_with_connection(
         current_board_start_tile.x,
         current_board_start_tile.y,
         Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT
      );
   current_board->initialize_pieces();
   Tracko::Piece *start_piece = current_board->get_piece(current_board_start_tile.x, current_board_start_tile.y);
   start_piece->reveal();

   // Load the new level
   AllegroFlare::Levels::Base *loaded_level = game_configuration->load_level_by_identifier(level_identifier);
   if (loaded_level)
   {
      // TODO: Consider how to have this level loading mechanism removed, specifically the dependency on the configuration
      // For now, confirm the type, and cast
      if (!loaded_level->is_type(Tracko::Gameplay::Level::TYPE))
      {
         throw std::runtime_error("Loaded level not of expected type");
      }
      current_level_identifier = level_identifier;
      current_level = static_cast<Tracko::Gameplay::Level*>(loaded_level);
   }
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"model_bin\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   camera.size = { 1920, 1080 };
   initialized = true;
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_activate: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_deactivate: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::update()
{

   return;
}

void Screen::render()
{
   //
   // Draw world
   //

   Tracko::BoardRenderer board_renderer(font_bin, current_board);
   current_board_placement.size = { board_renderer.infer_width(), board_renderer.infer_height() }; // ??

   // Draw the board
   camera.start_reverse_transform();
   current_board_placement.start_transform();
   board_renderer.render();
   current_board_placement.restore_transform();
   camera.restore_transform();

   //
   // Draw hud
   //

   // Draw the swap piece
   AllegroFlare::Placement2D swap_piece_placement;
   swap_piece_placement.position = { 320, 1080 - 200 };

   Tracko::PieceRenderer piece_renderer(font_bin, current_board->get_swap_piece());
   swap_piece_placement.size = { piece_renderer.get_width(), piece_renderer.get_height() };

   swap_piece_placement.start_transform();
   piece_renderer.render();
   swap_piece_placement.restore_transform();

   //ALLEGRO_FONT *font = obtain_font();
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2 - 30, ALLEGRO_ALIGN_CENTER, "Hello");

   return;
}

void Screen::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(game_event))
   {
      std::stringstream error_message;
      error_message << "[Screen::game_event_func]: error: guard \"game_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::game_event_func: error: guard \"game_event\" not met");
   }
   // game_configuration->handle_game_event(game_event);
   return;
}

void Screen::primary_update_func(double time_now, double delta_time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::primary_update_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::primary_update_func: error: guard \"initialized\" not met");
   }
   // Update stuff here (take into account delta_time)
   update();
   return;
}

void Screen::primary_render_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::primary_render_func: error: guard \"initialized\" not met");
   }
   // Render stuff here
   render();
   return;
}

void Screen::perform_primary_board_action()
{
   Tracko::Piece *piece_at_cursor = current_board->get_piece_at_cursor();

   if (piece_at_cursor->infer_can_reveal())
   {
      piece_at_cursor->reveal();
   }
   else if (current_board->can_swap())
   {
      current_board->swap();
   }
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* ev)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_char_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_char_func: error: guard \"ev\" not met");
   }
   switch (ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         current_board->move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
         current_board->move_cursor_down();
      break;

      case ALLEGRO_KEY_LEFT:
         current_board->move_cursor_left();
      break;

      case ALLEGRO_KEY_RIGHT:
         current_board->move_cursor_right();
      break;

      case ALLEGRO_KEY_ENTER:
         perform_primary_board_action();
         //universe.move_camera_left();
      break;

      //case ALLEGRO_KEY_S: {
         //bool command_pressed = ev->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         //if (command_pressed)
         //{
            //universe.save_score_to_filename();
            //handled = true;
         //}
      //} break;
      //case ALLEGRO_KEY_L: {
         //bool command_pressed = ev->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         //if (command_pressed)
         //{
            //universe.load_score_from_filename();
            //handled = true;
         //}
      //} break;
   }
   return;
}

void Screen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   using namespace AllegroFlare;
   //if (!is_processing_user_input()) return;

   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_RIGHT)
   {
      //player_velocity.x = 1;
      //chapter_select_element.rotate_carousel_right();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_LEFT)
   {
      //player_velocity.x = -1;
      //chapter_select_element.rotate_carousel_left();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      || virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      )
   {
      //select_menu_option();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_X)
   {
      //exit_screen();
   }
   //call_on_finished_callback_func(); // Consider technique to exit
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

ALLEGRO_FONT* Screen::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::obtain_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -32");
}


} // namespace Gameplay
} // namespace Tracko


