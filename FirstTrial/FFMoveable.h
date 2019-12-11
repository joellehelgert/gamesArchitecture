#pragma once

#include <Sge.h>
#include "ViewsEnum.h"

class FFMoveable final : public powidl::Component {
public:

	/** Constructor */
	FFMoveable();

	FFMoveable(Views view, powidl::Vector2 direction);
	
	Views getView();
	powidl::Vector2 getForwardVector();

	void setView(Views view);
	void setForwardVector(powidl::Vector2 direction);


	// Inherited via Component
	virtual std::unique_ptr<powidl::Component> clone() override;
private:
	Views m_view;
	powidl::Vector2 m_forward;
};