#pragma once


#include <AllegroFlare/AssetStudio/Database.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Int2D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <Tracko/Board.hpp>
#include <Tracko/GameConfigurations/Main.hpp>
#include <Tracko/Gameplay/Level.hpp>
#include <Tracko/Piece.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>


namespace Tracko
{
   namespace Gameplay
   {
      class Screen : public AllegroFlare::Screens::Gameplay
      {
      public:
         static constexpr char* DEFAULT_DATA_FOLDER_PATH = (char*)"[unset-data_folder_path]";
         static constexpr char* TYPE = (char*)"Tracko/Gameplay/Screen";

      private:
         enum State
         {
            STATE_UNDEF = 0,
            STATE_LEVEL_LOADED,
            STATE_REVEALING,
            STATE_COUNTDOWN_TO_START,
            STATE_PLAYING,
            STATE_LEVEL_WON,
            STATE_LEVEL_LOST,
            STATE_EXITING,
            STATE_EXITED,
         };
         std::string data_folder_path;
         AllegroFlare::AssetStudio::Database* asset_studio_database;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         Tracko::GameConfigurations::Main* game_configuration;
         std::string current_level_identifier;
         Tracko::Gameplay::Level* current_level;
         AllegroFlare::Camera2D camera;
         AllegroFlare::Camera3D camera3;
         Tracko::Board* current_board;
         Tracko::Piece* current_board_current_filling_piece;
         AllegroFlare::Int2D current_board_current_filling_piece_coordinates;
         std::string train_icon_bitmap_identifier;
         bool game_started;
         bool level_won;
         bool fast_train_mode_activated;
         AllegroFlare::Placement2D current_board_placement;
         uint32_t state;
         bool state_is_busy;
         float state_changed_at;
         bool initialized;

      protected:


      public:
         Screen();
         virtual ~Screen();

         void set_data_folder_path(std::string data_folder_path);
         void set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_model_bin(AllegroFlare::ModelBin* model_bin);
         void set_game_configuration(Tracko::GameConfigurations::Main* game_configuration);
         void set_train_icon_bitmap_identifier(std::string train_icon_bitmap_identifier);
         std::string get_data_folder_path() const;
         AllegroFlare::EventEmitter* get_event_emitter() const;
         Tracko::GameConfigurations::Main* get_game_configuration() const;
         std::string get_train_icon_bitmap_identifier() const;
         bool get_level_won() const;
         uint32_t get_state() const;
         bool get_initialized() const;
         AllegroFlare::AssetStudio::Database* &get_asset_studio_database_ref();
         bool current_level_is_final_level();
         virtual void load_level_by_identifier(std::string level_identifier="[unset-level_identifier]") override;
         void initialize();
         void start_game();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void trigger_level_won();
         void trigger_level_lost();
         void trigger_gameplay_exit();
         void update();
         void update_gameplay();
         void render();
         virtual void game_event_func(AllegroFlare::GameEvent* game_event=nullptr) override;
         virtual void primary_update_func(double time_now=0.0f, double delta_time=1.0f) override;
         virtual void primary_render_func() override;
         void perform_primary_board_action();
         void activate_fast_train_mode();
         virtual void key_char_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
         void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
         void update_state(float time_now=al_get_time());
         static bool is_valid_state(uint32_t state=STATE_UNDEF);
         bool is_state(uint32_t possible_state=STATE_UNDEF);
         float infer_current_state_age(float time_now=al_get_time());
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_banner_font();
      };
   }
}



