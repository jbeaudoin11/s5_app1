#include "Accel.h"

Accel::Accel(int addr) {
	
	_addr = addr << 1;
	_initI2C();
	_initGPIO();
	
	 _offset_x = 0;
	 _offset_y = 0;
	 _offset_z = 0;
	 _offset = 0;
	 _angle = 0;
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

void Accel::_initGPIO() {
	*(LPC_PINCON_PINSEL1) &= ~(3<<17);
	*(LPC_GPIO0_FIODIR) |= (1<<24);
	*(LPC_PINCON_PINMODE1) |= (3<<17);
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

float Accel::_capInterval(float val, float _min, float _max) {
	// Make sure the value is cap in the interval
	
	if(val > 0) {
		return min(val, _max);
	} else {
		return max(val, _min);
	}
}




void Accel::update() {
	
	int activated = 0;
	int value = ((*(LPC_GPIO0_FIOPIN) & (1 <<24))>> 24);
	//printf("Button = %d\n",value);
	if(value){
		activated = 1;
	}
	
	_readBufferFrom(OUT_X_MSB, _data_buffer, 3);
	
	// Set X in g
	_x = (float) _data_buffer[0];
	if(_x > 127) {
		_x -= 255;
	}
	_x = _capInterval(_x * 4.0 / 256.0, -1.0, 1.0);

	// Set Y in g
	_y = (float) _data_buffer[1];
	if(_y > 127) {
		_y -= 255;
	}
	_y = _capInterval(_y * 4.0 / 256.0, -1.0, 1.0);

	// Set X in g
	_z = (float) _data_buffer[2];
	if(_z > 127) {
		_z -= 255;
	}
	_z = _capInterval(_z * 4.0 / 256.0, -1.0, 1.0);
	
	if(activated){
		//_offset_x = _x;
		//_offset_y = _y;
		//_offset_z = 1-_z;
		_offset = _angle;
	}
			
	_angle = _rad2deg(asin(_x));
	if(_z < 0) {
		_angle = (_x >= 0.0 ? 180.0:-180.0) - _angle;
	}
		//printf("_x %0.2f -- offset_x %0.2f -- x() %0.2f \n", _x, _offset_x, x());
//	printf("_angle %0.2f -- offset %0.2f -- diff %0.2f -- a() %0.2f \n", _angle, _offset, _angle - _offset, a());
//	
}

float Accel::x() {
	//return _capInterval(_x + (_x >= 0.0? -_offset_x:_offset_x),-1.0,1.0);
	return _x;
}
float Accel::y() {
	//return _capInterval(_y + (_y >= 0.0? -_offset_y:_offset_y),-1.0,1.0);
	return _y;
}
float Accel::z() {
	//return _capInterval(_z + (_z >= 0.0? -_offset_z:_offset_z),-1.0,1.0);
	return _z;
}
float Accel::a() {	
//	return _angle + (_angle >= 0.0? -_offset:(360 - _offset));
	
	if(_angle < 0) {
		if(_angle - _offset > -180) {
			return _angle - _offset;
		} else {
			return _angle + (360 - _offset);
		}
	} else {
		return _angle - _offset;
	}
}
