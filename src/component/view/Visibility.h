//
// Created by Dawid Drozd aka Gelldur on 6/17/16.
//

#pragma once

#include <Component.h>

/**
 * Implementation is environment specific
 */
class Visibility : public Component
{
	using inherited = Component;
public:
	Visibility()
			: inherited()
	{
	}

	enum Visible
	{
		VISIBLE, INVISIBLE, GONE
	};
	virtual void setVisibility(Visible visible);

	COMPONENT_TO_STRING(Visibility)

	static Visibility& getNullObject();
};

