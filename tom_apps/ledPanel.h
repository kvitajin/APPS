/*
 * ledPanel.h
 *
 *  Created on: Sep 27, 2018
 *      Author: mic0357
 */

#ifndef LEDPANEL_H_
#define LEDPANEL_H_

class LedPanel {
public:
	LedPanel();
	virtual ~LedPanel();
	void shiftLeds();
};

#endif /* LEDPANEL_H_ */
