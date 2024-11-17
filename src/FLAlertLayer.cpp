#include <Geode/modify/FLAlertLayer.hpp>

#define PREFERRED_HOOK_PRIO (-2123456789)

using namespace geode::prelude;

class $modify(MyFLAlertLayer, FLAlertLayer) {
	static void onModify(auto & self)
	{
		(void) self.setHookPriority("FLAlertLayer::init", PREFERRED_HOOK_PRIO);
	}
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
		std::string titleAsString = title;
		std::string descAsString = desc;
		if (titleAsString != "Enable this in Eclipse Menu instead!" && !utils::string::endsWith(descAsString, "--RayDeeUx") && !utils::string::contains(descAsString, "I've written this feature for Eclipse Menu as well.") && !utils::string::contains(descAsString, "enable it there instead")) {
			return FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale);
		}
		return FLAlertLayer::init(delegate, title, desc, btn1, btn2, 420.f, true, 320.f, 1.0f);
	}
};