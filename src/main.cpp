#include <Geode/loader/SettingV3.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
	listenForSettingChanges<bool>("muteLevelSFX", [](bool muteLevelSFX) {
		if (Utils::isEclipse() && muteLevelSFX) Utils::showEclipseMenuAlert("muteLevelSFX");
	});
	listenForSettingChanges<bool>("muteLevelOnDeath", [](bool muteLevelOnDeath) {
		if (Utils::isEclipse() && muteLevelOnDeath) Utils::showEclipseMenuAlert("muteLevelOnDeath");
	});
	listenForSettingChanges<bool>("muteRewardsSFX", [](bool muteRewardsSFX) {
		if (Utils::isEclipse() && muteRewardsSFX) Utils::showEclipseMenuAlert("muteRewardsSFX");
	});
	listenForSettingChanges<bool>("hideLevelCompleteVFX", [](bool hideLevelCompleteVFX) {
		if (Utils::isEclipse() && hideLevelCompleteVFX) Utils::showEclipseMenuAlert("hideLevelCompleteVFX");
	});
}