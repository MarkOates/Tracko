

#include <Tracko/Gameplay/Screen.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <Tracko/BoardRenderer.hpp>
#include <Tracko/GameConfigurations/Main.hpp>
#include <Tracko/Gameplay/Level.hpp>
#include <Tracko/PieceRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
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
   , camera3({})
   , current_board(nullptr)
   , current_board_current_filling_piece(nullptr)
   , current_board_current_filling_piece_coordinates({})
   , game_started(false)
   , current_board_placement({})
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
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


AllegroFlare::EventEmitter* Screen::get_event_emitter() const
{
   return event_emitter;
}


Tracko::GameConfigurations::Main* Screen::get_game_configuration() const
{
   return game_configuration;
}


uint32_t Screen::get_state() const
{
   return state;
}


bool Screen::get_initialized() const
{
   return initialized;
}


AllegroFlare::AssetStudio::Database* &Screen::get_asset_studio_database_ref()
{
   return asset_studio_database;
}


bool Screen::current_level_is_final_level()
{
   std::string last_level_identifier = "level_1234";
   return current_level_identifier == last_level_identifier;
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

   // Set state
   //set_state(STATE_LEVEL_LOADED);

   // Reset the camera2D position
   camera.position = { 0, 0 };

   // Reset the camera3D position
   camera3.position = { 0, 0 };
   camera3.stepout = 0;
   camera3.tilt = 0.0;
   camera3.spin = 0.0;

   // Reset the game started counter
   game_started = false;

   // DEVELOPMENT: build random board
   if (current_board) delete current_board;

   if (level_identifier == "level_1")
   {
      current_board = new Tracko::Board;
      current_board->set_start_tile_coordinates({ 0, 2 });
      current_board->set_start_tile_start_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT);
      current_board->set_exit_tile_coordinates({ 5, 1 });
      current_board->set_exit_tile_exit_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT);
      current_board->resize(6, 4);
      current_board->fill_with_random_types(2);
      current_board->set_random_tile_with_connection(
            current_board->get_start_tile_coordinates().x,
            current_board->get_start_tile_coordinates().y,
            Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT,
            3
         );
      current_board->initialize_pieces();
      Tracko::Piece *start_piece = current_board->get_piece(
            current_board->get_start_tile_coordinates().x,
            current_board->get_start_tile_coordinates().y
         );
      start_piece->reveal();
      current_level_identifier = "level_1";
   }
   else if (level_identifier == "level_1234")
   {
      current_board = new Tracko::Board;
      current_board->set_start_tile_coordinates({ 0, 1 });
      current_board->set_start_tile_start_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT);
      current_board->set_exit_tile_coordinates({ 6, 3 });
      current_board->set_exit_tile_exit_connecting_position(Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_RIGHT);
      current_board->resize(7, 5);
      current_board->fill_with_random_types(1234);
      current_board->set_random_tile_with_connection(
            current_board->get_start_tile_coordinates().x,
            current_board->get_start_tile_coordinates().y,
            Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_LEFT
         );
      current_board->initialize_pieces();
      Tracko::Piece *start_piece = current_board->get_piece(
            current_board->get_start_tile_coordinates().x,
            current_board->get_start_tile_coordinates().y
         );
      start_piece->reveal();
      current_level_identifier = "level_1234";
   }
   else
   {
      AllegroFlare::Logger::throw_error(
            "Tracko::Gameplay::Screen",
            "Case not found to load level with identifier \"" + level_identifier + "\"."
         );
   }

   // Set state
   set_state(STATE_LEVEL_LOADED);

   /*
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
   */
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

void Screen::start_game()
{
   if (!((!game_started)))
   {
      std::stringstream error_message;
      error_message << "[Screen::start_game]: error: guard \"(!game_started)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::start_game: error: guard \"(!game_started)\" not met");
   }
   game_started = true;
   current_board_current_filling_piece_coordinates = current_board->get_start_tile_coordinates();
   current_board_current_filling_piece =
      current_board->get_piece(
         current_board_current_filling_piece_coordinates.x,
         current_board_current_filling_piece_coordinates.y
      );
   current_board_current_filling_piece->set_entrance_connecting_position(
         current_board->get_start_tile_start_connecting_position()
      );
   set_state(STATE_COUNTDOWN_TO_START);
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

void Screen::trigger_level_won()
{
   set_state(STATE_LEVEL_WON);
}

void Screen::trigger_level_lost()
{
   set_state(STATE_LEVEL_LOST);
}

void Screen::trigger_gameplay_exit()
{
   set_state(STATE_EXITING);
}

void Screen::update()
{
   update_state();
   if (is_state(STATE_PLAYING)) update_gameplay();
   return;
}

void Screen::update_gameplay()
{
   if (!(is_state(STATE_PLAYING)))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_gameplay]: error: guard \"is_state(STATE_PLAYING)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_gameplay: error: guard \"is_state(STATE_PLAYING)\" not met");
   }
   double fill_rate = 1.0 / 60.0; // TODO: Use a more reliable time step
   fill_rate /= 8.0f; // TODO: Use a bpm to sync with music(?)
   if (current_board_current_filling_piece && current_board)
   {
      bool was_filled = false;
      float overflow = 0.0f;
      Tracko::Piece::ConnectingPosition exit_connecting_position =
         Tracko::Piece::ConnectingPosition::CONNECTING_POSITION_UNDEF;
      std::tie(was_filled, overflow, exit_connecting_position) =
         current_board_current_filling_piece->fill_with_amount(fill_rate);

      if (was_filled)
      {
         // TODO: Handle going to next piece
         bool current_piece_is_last_piece = false;

         // TODO: Test this conditional
         if (current_board->get_exit_tile_coordinates().x == current_board_current_filling_piece_coordinates.x
               && current_board->get_exit_tile_coordinates().y == current_board_current_filling_piece_coordinates.y
               && exit_connecting_position == current_board->get_exit_tile_exit_connecting_position()
            )
         {
            current_piece_is_last_piece = true;
         }

         if (current_piece_is_last_piece)
         {
            // Level won! Jump to win state
            // TODO: Handle this case
            //throw std::runtime_error("Game won!");
            trigger_level_won();
         }
         else
         {
            Tracko::Piece* connecting_to_piece = nullptr;
            std::pair<int, int> connecting_to_coordinates = { 0, 0 };

            std::tie(connecting_to_piece, connecting_to_coordinates) = current_board->get_connecting_to_piece(
                  current_board_current_filling_piece_coordinates.x,
                  current_board_current_filling_piece_coordinates.y,
                  exit_connecting_position
               );

            Tracko::Piece::ConnectingPosition next_entrance_connecting_position =
               current_board->get_inverse_connection_position(exit_connecting_position);

            bool pieces_can_connect = true;
            if (connecting_to_piece == nullptr)
            {
               pieces_can_connect = false;
            }
            else
            {
               if (!connecting_to_piece->infer_is_available_for_connection()) pieces_can_connect = false;
               if (!connecting_to_piece->has_connecting_position(next_entrance_connecting_position))
                  pieces_can_connect = false;
            }

            if (!pieces_can_connect)
            {
               // Lost game! Jump to you lose state
               // TODO: Handle this case
               //throw std::runtime_error("Game lost!");
               trigger_level_lost();
            }
            else
            {
               // TODO: Test this section

               // Get the new entrance position
               //Tracko::Piece::ConnectingPosition next_entrance_connecting_position =
                  //current_board->get_inverse_connection_position(exit_connecting_position);

               // These variables are not properly assigned
               current_board_current_filling_piece_coordinates =
                  { connecting_to_coordinates.first, connecting_to_coordinates.second };
               current_board_current_filling_piece =
                  current_board->get_piece(
                     current_board_current_filling_piece_coordinates.x,
                     current_board_current_filling_piece_coordinates.y
                  );
               current_board_current_filling_piece->set_entrance_connecting_position(
                     next_entrance_connecting_position
                  );
            }
         }
      }
   }
   return;
}

void Screen::render()
{
   //al_draw_bitmap(bitmap_bin->auto_get("background-general-01.jpg"), 0, 0, 0);

   //if (get_background()) get_background()->render();
   //
   // Draw world
   //

   Tracko::BoardRenderer board_renderer(bitmap_bin, font_bin, model_bin, current_board);
   current_board_placement.size = { board_renderer.infer_width(), board_renderer.infer_height() }; // ??
   current_board_placement.scale = { 0.0075, -0.0075 };

   // Draw the board
   camera3.tilt = -0.6;
   //camera3.stepout += 0.1;
   camera3.stepout = AllegroFlare::Vec3D(0, -0.1, 10);
   camera3.zoom = 2.0;
   camera3.setup_projection_on(al_get_target_bitmap()); // ???
   //AllegroFlare::Model3D *model = model_bin->auto_get("centered_unit_cube-02.obj");
   //ALLEGRO_BITMAP *texture = bitmap_bin->auto_get("tiles_4x3-01-horizontal-01.png");
   //AllegroFlare::Model3D *model = model_bin->auto_get("tiles_4x3-01-horizontal-01.obj");
   //AllegroFlare::Placement3D piece_placement;
   //float scale = 0.25;
   //piece_placement.scale = { scale, scale, scale };
   //piece_placement.rotation += { 0.25, 0.0, 0.0 };
   //model->set_texture(texture);

   //piece_placement.start_transform();
   //model->draw();
   //piece_placement.restore_transform();
   //camera3.start_reverse_transform();
   // camera.start_reverse_transform();
   current_board_placement.start_transform();
   board_renderer.render();
   //board_renderer.render_models();
   current_board_placement.restore_transform();
   //camera.restore_transform();
   //camera3.restore_transform();

   //
   // Draw hud
   //

   // Draw the swap piece
   camera.setup_dimensional_projection(al_get_target_bitmap());
   camera.start_reverse_transform();
   AllegroFlare::Placement2D swap_piece_placement;
   swap_piece_placement.position = { -1920 / 2 + 100, 1080 / 2 - 100 }; //320, 1080 - 200 };

   Tracko::PieceRenderer piece_renderer;
   piece_renderer.set_font_bin(font_bin);
   piece_renderer.set_bitmap_bin(bitmap_bin);
   piece_renderer.set_model_bin(model_bin);
   piece_renderer.set_piece(current_board->get_swap_piece());
   swap_piece_placement.size = { piece_renderer.get_width(), piece_renderer.get_height() };

   swap_piece_placement.start_transform();
   piece_renderer.render();
   swap_piece_placement.restore_transform();
   camera.restore_transform();

   // Draw banners based on state:

   if (is_state(STATE_LEVEL_WON))
   {
      ALLEGRO_FONT *font = obtain_banner_font();
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2 - 220, ALLEGRO_ALIGN_CENTER, "Game Won");
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2, ALLEGRO_ALIGN_CENTER, "Press ENTER");
   }
   else if (is_state(STATE_LEVEL_LOST))
   {
      ALLEGRO_FONT *font = obtain_banner_font();
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2 - 220, ALLEGRO_ALIGN_CENTER, "Game Lost");
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2, ALLEGRO_ALIGN_CENTER, "Press ENTER");
   }
   else if (is_state(STATE_REVEALING))
   {
      ALLEGRO_FONT *font = obtain_banner_font();
      //int count = 5 - (infer_current_state_age() + 1);
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2 - 120, ALLEGRO_ALIGN_CENTER, "READY");
   }
   else if (is_state(STATE_COUNTDOWN_TO_START))
   {
      ALLEGRO_FONT *font = obtain_banner_font();
      int count = 5 - (infer_current_state_age() + 1);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2 - 120, ALLEGRO_ALIGN_CENTER, "%d", count);
   }

   //ALLEGRO_FONT *font = obtain_font();
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 1080/2 - 30, ALLEGRO_ALIGN_CENTER, "Hello");
   //if (foreground) foreground->render();

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
   bool in_playing_state = is_state(STATE_COUNTDOWN_TO_START) || is_state(STATE_PLAYING);
   bool in_win_or_loss_state = is_state(STATE_LEVEL_WON) || is_state(STATE_LEVEL_LOST);

   if (in_playing_state)
   {
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

         case ALLEGRO_KEY_SPACE:
            perform_primary_board_action();
         break;

         //case ALLEGRO_KEY_SPACE:
            //if (!game_started) start_game();
         //break;
      }
   }
   else if (in_win_or_loss_state)
   {
      switch (ev->keyboard.keycode)
      {
         case ALLEGRO_KEY_ENTER:
            trigger_gameplay_exit();
         break;
      }
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

void Screen::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_state: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_LEVEL_LOADED:
      break;

      case STATE_REVEALING:
      break;

      case STATE_COUNTDOWN_TO_START:
      break;

      case STATE_PLAYING:
      break;

      case STATE_LEVEL_WON:
      break;

      case STATE_LEVEL_LOST:
      break;

      case STATE_EXITING:
      break;

      case STATE_EXITED:
      break;

      default:
         AllegroFlare::Logger::throw_error(
            "ClassName::set_state",
            "Unable to handle case for state \"" + std::to_string(state) + "\""
         );
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void Screen::update_state(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_state: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   switch (state)
   {
      case STATE_LEVEL_LOADED:
         set_state(STATE_REVEALING);
      break;

      case STATE_REVEALING: {
         double revealing_duration = 3.0;
         if (age >= revealing_duration)
         {
            start_game();
         }
      } break;

      case STATE_COUNTDOWN_TO_START:
         if (age > 3.0) set_state(STATE_PLAYING);
      break;

      case STATE_PLAYING:
      break;

      case STATE_LEVEL_WON:
      break;

      case STATE_LEVEL_LOST:
      break;

      case STATE_EXITING:
         if (age > 2.0)
         {
            set_state(STATE_EXITED);
            call_on_finished_callback_func();
         }
      break;

      case STATE_EXITED:
      break;

      default:
         AllegroFlare::Logger::throw_error(
            "ClassName::update_state",
            "Unable to handle case for state \"" + std::to_string(state) + "\""
         );
      break;
   }

   return;
}

bool Screen::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_LEVEL_LOADED,
      STATE_REVEALING,
      STATE_COUNTDOWN_TO_START,
      STATE_PLAYING,
      STATE_LEVEL_WON,
      STATE_LEVEL_LOST,
      STATE_EXITING,
      STATE_EXITED
   };
   return (valid_states.count(state) > 0);
}

bool Screen::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float Screen::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
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

ALLEGRO_FONT* Screen::obtain_banner_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::obtain_banner_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::obtain_banner_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Oswald-Medium.ttf -200");
}


} // namespace Gameplay
} // namespace Tracko


