#include "Accel.h"

Accel::Accel(int addr) {
	
	_addr = addr << 1;
	_initI2C();
}

void Accel::_initI2C() {
	_accel_i2c = new I2C(p28, p27);

	_standby();
	
	_setScale(SCALE_2G);
	_setOdr(ODR_6);
	_setMode();
	_set8Bit();
	
	_active();
}

void Accel::_writeTo(AccRegister reg, char data) {
	char buffer[2] = {reg, data};
	_accel_i2c->write(_addr, buffer, 2);
}

char Accel::_readFrom(AccRegister reg) {
	char data = 0;
	
	_readBufferFrom(reg, &data, 1);
	
	return data;
}
void Accel::_readBufferFrom(AccRegister reg, char *buffer, char len) {
	char _reg[1] = {reg};
	
	_accel_i2c->write(_addr, _reg, 1, true);
	_accel_i2c->read(_addr, buffer, len);
}

void Accel::_standby() {
	char c = _readFrom(CTRL_REG1);
	_writeTo(CTRL_REG1, c & ~(0b00000001));
}
void Accel::_active() {
	char c = _readFrom(CTRL_REG1);
	_writeTo(CTRL_REG1, c | 0b00000001);	
}

void Accel::_setScale(AccScale scale) {
	char c = _readFrom(XYZ_DATA_CFG);
	
	c &= ~0b00000011; // Reset scale
	c |= scale;
	
	_writeTo(XYZ_DATA_CFG, c);
}
void Accel::_setOdr(AccOdr odr) {
	char c = _readFrom(CTRL_REG1);
	
	c &= ~0b00111000; // Reset odr
	c |= odr;
	
	_writeTo(CTRL_REG1, c);
}
void Accel::_setMode() {
	char c = _readFrom(CTRL_REG2);
	
	c &= ~0b00000011; // Reset odr
	c |= 0b00000001; // Low noise Low Power
	
	_writeTo(CTRL_REG2, c);
}
void Accel::_set8Bit() {
	char c = _readFrom(CTRL_REG1);
	
	c &= ~0b00000010; // Reset 
	c |= 0b00000010; // 
	
	_writeTo(CTRL_REG1, c);
}

float Accel::_rad2deg(float rad) {
	return rad * 180.0 / PI;
}





void Accel::update() {
	
	_readBufferFrom(OUT_X_MSB, _data_buffer, 3);
	
	// Set X in g
	_x = (float) _data_buffer[0];
	if(_x > 127) {
		_x -= 255;
	}
	_x = _x * 4.0 / 256.0;
	
	// Set Y in g
	_y = (float) _data_buffer[1];
	if(_y > 127) {
		_y -= 255;
	}
	_y = _y * 4.0 / 256.0;
	
	// Set X in g
	_z = (float) _data_buffer[2];
	if(_z > 127) {
		_z -= 255;
	}
	_z = _z * 4.0 / 256.0;
	
	
	// Set Angle in deg
	_angle = _rad2deg(asin(_x));
	if(_z < 0) {
		_angle = (_x >= 0 ? 180:-180) - _angle;
	}
//	
//	printf("A %0.2f -- X %0.2f -- Y %0.2f -- Z %0.2f\n", _angle, _x, _y, _z);
	
}

float Accel::x() {
	return _x;
}
float Accel::y() {
	return _y;
}
float Accel::z() {
	return _z;
}
float Accel::a() {
	return _angle;
}
