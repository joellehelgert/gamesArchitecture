#include "FFMoveable.h"

using namespace std;
using namespace powidl;

FFMoveable::FFMoveable()
{

	m_view = WideView;
	m_forward = powidl::Vector2(1, 0);

}

FFMoveable::FFMoveable(Views view, powidl::Vector2 direction)
{
	m_view = view;
	m_forward = direction;
}

Views FFMoveable::getView()
{
	return m_view;
}

powidl::Vector2 FFMoveable::getForwardVector()
{
	return powidl::Vector2();
}

void FFMoveable::setView(Views view)
{
	m_view = view;
}

void FFMoveable::setForwardVector(powidl::Vector2 direction)
{
	m_forward = direction;
}

std::unique_ptr<powidl::Component> FFMoveable::clone()
{
	// Use copy-constructor to create clone of this component.
	return std::make_unique<FFMoveable>(*this);
}
