#include <Geode/modify/GameObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (3999)

using namespace geode::prelude;

class $modify(MyGameObject, GameObject) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("GameObject::activateObject", PREFERRED_HOOK_PRIO);
	}
	virtual void activateObject() {
		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled || LevelEditorLayer::get()) return GameObject::activateObject();
		if (this->m_objectID == 1520 && manager->disableShakeTrigger) return;
		const std::string& noEffects = manager->noEffects;
		if (noEffects == "Ignore") return GameObject::activateObject();
		if (noEffects == "Enable on Visible, Disable on Invis.") {
			this->m_hasNoEffects = !this->m_isHide && !this->m_isInvisible && GameObject::getOpacity() > 0;
		} else if (noEffects == "Disable on Visible, Enable on Invis.") {
			this->m_hasNoEffects = !(!this->m_isHide && !this->m_isInvisible && GameObject::getOpacity() > 0);
		} else if (utils::string::endsWith(noEffects, " (+ Ignore Invis.)")) {
			// if "(+ Ignore Invis.)" is found at the end, need to perform invis check
			const bool isInvis = this->m_isHide || this->m_isInvisible || GameObject::getOpacity() <= 0;
			if (!isInvis) this->m_hasNoEffects = utils::string::startsWith(noEffects, "Force Enable ");
		} else {
			// brute force override
			this->m_hasNoEffects = noEffects == "Force Enable";
		}
		GameObject::activateObject();
	}
};