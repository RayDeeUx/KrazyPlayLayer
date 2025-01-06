#include "Utils.hpp"
#include <cmath>
#include <regex>
#include <random>

namespace Utils {

	template<class T> T getSetting(const std::string_view setting) { return Mod::get()->getSettingValue<T>(setting); }

	bool getBool(const std::string_view setting) { return getSetting<bool>(setting); }
	
	int64_t getInt(const std::string_view setting) { return getSetting<int64_t>(setting); }
	
	double getDouble(const std::string_view setting) { return getSetting<double>(setting); }

	std::string getString(const std::string_view setting) { return getSetting<std::string>(setting); }

	ccColor3B getColor(const std::string_view setting) { return getSetting<ccColor3B>(setting); }

	ccColor4B getColorAlpha(const std::string_view setting) { return getSetting<ccColor4B>(setting); }

	bool modEnabled() { return getBool("enabled"); }
	
	bool isModLoaded(std::string modID) { return Loader::get()->isModLoaded(modID); }

	Mod* getMod(std::string modID) { return Loader::get()->getLoadedMod(modID); }

	std::string getModVersion(const Mod* mod) { return mod->getVersion().toNonVString(); }

	int getRandInt(int min, int max) {
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(min,max);

		return uni(rng);
	}

	void setBool(const std::string_view setting, bool value) { Mod::get()->setSettingValue<bool>(setting, value); }

	bool isEclipse() {
		return Utils::isModLoaded("eclipse.eclipse-menu");
	}

	void showEclipseMenuAlert(std::string settingName) {
		if (!Utils::isEclipse()) return;
		FLAlertLayer::create(
			"Hey there!",
			"<cy>Please</c> <cl>enable this in Eclipse Menu</c><cy>; I have written this feature for Eclipse Menu too.</c> Thanks!\n--RayDeeUx",
			"Close"
		)->show();
	}

}
