#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/Levels/Base.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <AllegroFlare/Runners/Complete.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Screens/PauseScreen.hpp>
#include <AllegroFlare/Screens/Subscreen/Screen.hpp>
#include <Tracko/ForwardDeclarations/Tracko/GameConfigurations/Main.hpp>
#include <Tracko/ForwardDeclarations/Tracko/Gameplay/Screen.hpp>
#include <Tracko/Gameplay/Screen.hpp>
#include <Tracko/SharedBackground.hpp>
#include <Tracko/SharedForeground.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace Tracko
{
   namespace GameConfigurations
   {
      class Main : public AllegroFlare::GameConfigurations::Complete
      {
      public:
         static constexpr char* TYPE = (char*)"Tracko/GameConfigurations/Main";

      private:
         Tracko::Gameplay::Screen* primary_gameplay_screen;
         AllegroFlare::Screens::Subscreen::Screen* primary_gameplay_subscreen;
         AllegroFlare::Screens::PauseScreen* pause_screen;
         Tracko::SharedBackground* shared_background;
         Tracko::SharedForeground* shared_foreground;

      protected:


      public:
         Main();
         virtual ~Main();

         virtual std::string app_title() override;
         virtual std::string title_screen_title() override;
         virtual std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> build_achievements() override;
         virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_background() override;
         virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_foreground() override;
         virtual AllegroFlare::Screens::Gameplay* create_primary_gameplay_screen(AllegroFlare::Runners::Complete* runner=nullptr) override;
         virtual void handle_primary_gameplay_screen_finished() override;
         virtual void before_activate_screen_callback(std::string screen_identifier_that_will_activate="[unset-screen_identifier_that_will_activate]", std::string currently_active_screen_identifier="[unset-currently_active_screen_identifier]") override;
         virtual AllegroFlare::Screens::Subscreen::Screen* create_primary_gameplay_subscreen(AllegroFlare::Runners::Complete* runner=nullptr) override;
         virtual AllegroFlare::Screens::PauseScreen* create_pause_screen(AllegroFlare::Runners::Complete* runner=nullptr) override;
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_logos_storyboard_pages() override;
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_storyboard_pages() override;
         virtual std::vector<std::pair<std::string, std::string>> build_title_screen_menu_options() override;
         virtual void load_audio_controller(AllegroFlare::AudioController* audio_controller=nullptr) override;
         virtual void load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr) override;
         virtual void setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr) override;
         virtual std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> build_save_slots_for_load_a_saved_game_screen() override;
         virtual void handle_game_event(AllegroFlare::GameEvent* game_event=nullptr) override;
         void continue_from_last_save();
         virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]") override;
         virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[identifier-discarded]") override;
         virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string identifier="[unset-identifier]") override;
      };
   }
}



