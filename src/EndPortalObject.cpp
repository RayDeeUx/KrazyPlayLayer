#include <Geode/modify/EndPortalObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEndPortalObject, EndPortalObject) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void updateEndPos(bool p0) {
		EndPortalObject::updateEndPos(p0);
		if (!Utils::modEnabled()) return;
		if (Utils::getBool("hideEndPortalGradient")) this->m_gradientBar->setVisible(false);
		if (!Utils::getBool("noEndPortalParticles")) return;
		m_fields->manager->endPortalX = this->getPositionX();
		m_fields->manager->endPortalY = this->getPositionY();
	}
};