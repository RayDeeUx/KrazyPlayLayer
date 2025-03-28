#include <ninxout.options_api/include/API.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

#define ADD_TOGGLE(displayName, settingsID, detailedDesc)\
	OptionsAPI::addPreLevelSetting<bool>(\
		displayName,\
		settingsID""_spr,\
		[](GJGameLevel*) {\
			const bool origValue = Mod::get()->getSettingValue<bool>(settingsID);\
			Mod::get()->setSettingValue<bool>(settingsID, !origValue);\
		},\
		[](GJGameLevel*) {\
			return Mod::get()->getSettingValue<bool>(settingsID);\
		},\
		"<cl>(From KrazyPlayLayer)</c>\n" detailedDesc\
	);

$on_mod(Loaded) {
	Manager::getSharedInstance()->load();

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

	listenForAllSettingChanges([](std::shared_ptr<SettingV3> setting){
		Manager::load();
	});

	if (!Mod::get()->getSettingValue<bool>("optionsAPI")) return;
	ADD_TOGGLE("Disable Shake Trigger", "disableShakeTrigger", "Disables shake triggers without disabling the shaking effect from completing levels.")
	ADD_TOGGLE("Hide Two Player Guide", "hideTwoPlayer", "Hide the Two Player guide when opening a two-player level.\n\n<cy>This does not *skip* the delay from showing the Two Player guide, it only hides the UI elements it adds to the screen.</c>")
	ADD_TOGGLE("Mute Level SFX", "muteLevelSFX", "<cl>Formerly part of ErysEdits; ported by me into Eclipse Menu.</c>\n\nDisables SFX/Edit SFX triggers.\n\n<cy>If Eclipse Menu is loaded, you will be asked to enable the equivalent option in Eclipse Menu, and this setting will be forcefully</c> <cr>disabled</c><cy>.</c>")
	ADD_TOGGLE("Mute Level Audio on Death", "muteLevelOnDeath", "<cl>Formerly part of ErysEdits; ported by me into Eclipse Menu.</c>\n\nMutes all level audio (Music + SFX) on player death.\n\n<cy>If Eclipse Menu is loaded, you will be asked to enable the equivalent option in Eclipse Menu, and this setting will be forcefully</c> <cr>disabled</c><cy>.</c>")
	ADD_TOGGLE("Mute Rewards SFX on Death", "muteRewardsSFX", "<cl>Formerly part of ErysEdits; ported by me into Eclipse Menu.</c>\n\nMutes all rewards SFX (orbs, diamonds, keys) when the player dies.\n\n<cy>If Eclipse Menu is loaded, you will be asked to enable the equivalent option in Eclipse Menu, and this setting will be forcefully</c> <cr>disabled</c><cy>.</c>")
	ADD_TOGGLE("Hide Level Complete VFX", "hideLevelCompleteVFX", "<cl>Formerly part of ErysEdits; ported by me into Eclipse Menu.</c>\n\nHides the explosion, fireworks, and particles seen when completing a level.\n\n<cy>If Eclipse Menu is loaded, you will be asked to enable the equivalent option in Eclipse Menu, and this setting will be forcefully</c> <cr>disabled</c><cy>.</c>")
	ADD_TOGGLE("Hide Dash Orb Particles", "noDashOrbParticles", "Hide the particle effects from <cl>dash orbs</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Custom Orb Particles", "noCustomOrbParticles", "Hide the particle effects from <cl>custom orbs</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Teleport Orb Particles", "noTeleportOrbParticles", "Hide the particle effects from <cl>teleport orbs</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Jump Ring Particles", "noJumpRingParticles", "Hide the particle effects from <cl>jump rings</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Jump Pad Particles", "noJumpPadParticles", "Hide the particle effects from <cl>jump pads</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Dual Portal Particles", "noDualPortalParticles", "Hide the particle effects from <cl>dual portals</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Teleport Portal Particles", "noTeleportPortalParticles", "Hide the particle effects from <cl>teleport portals</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Gamemode Portal Particles", "noGamemodePortalParticles", "Hide the particle effects from <cl>gamemode portals</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Mirror Portal Particles", "noMirrorPortalParticles", "Hide the particle effects from <cl>mirror portals</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Gravity Portal Particles", "noGravityPortalParticles", "Hide the particle effects from <cl>gravity portals</c> (including the <cg>green gravity portal</c>) inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Size Portal Particles", "noSizePortalParticles", "Hide the particle effects from <cl>size portals</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Speed Portal Particles", "noSpeedPortalParticles", "Hide the particle effects from <cl>speed portals</c> inside a level.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's particles.</c>")
	ADD_TOGGLE("Hide Collectible Particles", "noCollectibleParticles", "Hide the particle effects from <cl>collectible objects</c> inside a level.\n<cy>This does *not* hide the particles from picking up such collectible items.</c>\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's particles.</c>")
	ADD_TOGGLE("Hide Particles (Most Other Objects)", "noParticles", "Hide the particle effects from <cl>all objects not mentioned in prior settings</c> inside a level <cy>(besides particle objects)</c>.\n\n<cy>Technical limitations prevent mods from easily overriding an object's \"No Particles\" property to show the object's original particles.</c>")
	ADD_TOGGLE("Hide Ship/UFO/Wave/Swing BG Particles", "noParticlesWhenFlying", "Hide the particle effects that overlay your game when as a Ship, UFO, Wave, or Swing.")
	ADD_TOGGLE("Hide All Player Particles", "noPlayerParticles", "Hide the particle effects from various player actions, including running on the floor, flying the ship, controlling your swing, and jumping as a robot.")
	ADD_TOGGLE("Hide Speed Particles", "noSpeedParticles", "Hide the particle effects from activating speed portals.")
	ADD_TOGGLE("Hide Gold Coin Particles", "noGoldCoinParticles", "Hide the particle effects from gold coins.\n\n<cy>This does *not* hide the particles from picking up coins.</c>")
	ADD_TOGGLE("Hide User Coin Particles", "noCoinParticles", "Hide the particle effects from user coins.\n\n<cy>This does *not* hide the particles from picking up coins.</c>")
	ADD_TOGGLE("Hide End Portal Particles", "noEndPortalParticles", "Hide the particle effects from end portals in Classic levels.\n\n<cy>This affects all items that emit particles and share the same position as the end portal's particle effects.</c>.")
	ADD_TOGGLE("Hide End Portal Gradient", "hideEndPortalGradient", "Hide the gradient/glow from the end portal.")
	ADD_TOGGLE("Hide Player Dash Fire", "noDashFire", "Hide the dash fire animation when using a dash orb.")
	ADD_TOGGLE("Hide Player Dash Fire", "noRobotFire", "Hide the robot fire animation when jumping as a robot.")
	ADD_TOGGLE("Hide Player Swing Fire", "noSwingFire", "Hide the swing fire animation when being a swing.")
}