#ifndef MEASURES_H
#define	MEASURES_H

int getWindPWM();
void setWindSpeed(int windPot);
int measureWindSpeed();
int measureHumidity();
int measureTemperature();
void changeTemperature();

#endif	/* MEASURES_H */