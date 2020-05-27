#ifndef MEASURES_H
#define	MEASURES_H

int getWindPWM(void);
void setWindSpeed(int windPot);
int measureWindSpeed(void);
int measureHumidity(void);
int measureTemperature(void);
void changeTemperature(void);

#endif	/* MEASURES_H */