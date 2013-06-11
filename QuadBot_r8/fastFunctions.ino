// const float PI = 3.141592;
const float PIby2 = PI/2;


const float FSIN_TABLE[91] = {
0.000000, 0.017452, 0.034900, 0.052336, 0.069757, 0.087156, 0.104529, 0.121869, 0.139173, 0.156435, 0.173648, 0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275637, 0.292372, 0.309017, 0.325568, 0.342020, 0.358368, 0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.453991, 0.469472, 0.484810, 
0.500000, 0.515038, 0.529919, 0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615662, 0.629320, 0.642788, 0.656059, 0.669131, 0.681998, 0.694658, 0.707107, 0.719340, 0.731354, 0.743145, 0.754710, 0.766044, 0.777146, 0.788011, 0.798636, 0.809017, 0.819152, 0.829038, 0.838671, 0.848048, 0.857167, 
0.866025, 0.874620, 0.882948, 0.891007, 0.898794, 0.906308, 0.913546, 0.920505, 0.927184, 0.933580, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296, 0.974370, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.998630, 0.999391, 0.999848, 1.000000
};

const float FACOS_TABLE[51] = {
0.643501, 0.636804, 0.630047, 0.623226, 0.616339, 0.609385, 0.602361, 0.595265, 0.588093, 0.580844, 0.573513, 0.566098, 0.558596, 0.551003, 0.543314, 0.535527, 0.527635, 0.519636, 0.511523, 0.503291, 0.494934, 0.486446, 0.477819, 0.469046, 0.460118, 0.451027, 0.441761, 0.432311, 
0.422663, 0.412803, 0.402716, 0.392384, 0.381788, 0.370904, 0.359707, 0.348166, 0.336246, 0.323904, 0.311092, 0.297747, 0.283794, 0.26914, 0.253662, 0.237199, 0.21953, 0.200335, 0.179125, 0.155075, 0.126576, 0.089473, 0

};

int FloatToInt(float input){
	// this is an alternative to cast number directly, to avoid floor rounding

	int temp = (int)input; // floor-rounded input
	float dif = input - (float)temp;	// 
	if (dif < 0.5)	return temp;
	else			return temp+1;
}


float fsin(int deg){
	// check for pos/neg sign
	// get absolute value
	int sign = 1;
	if (deg<0){
		sign = -1;
		deg = -deg;
	}
	// make sure degree under 360
	while (deg>=360)     deg -= 360;

	if (deg<90)
		return sign * FSIN_TABLE[deg];
	else if ((deg>=90) && (deg<180))
		return sign * FSIN_TABLE[180-deg];
	else if ((deg>=180) && (deg<270))
		return sign * -1*FSIN_TABLE[deg-180];
	else //if ((deg>=270) && (deg<360))
		return sign * -1*FSIN_TABLE[360-deg];
}

float fcos(int deg){
	// get absolute value (symeric)
	if (deg<0)    deg = -deg;
	// make sure degree under 360
	while (deg>=360)     deg -= 360;

	if (deg<90)
		return FSIN_TABLE[90-deg];
	else if ((deg>=90) && (deg<180))
		return (-1*FSIN_TABLE[deg-90]);
	else if ((deg>=180) && (deg<270))
		return (-1*FSIN_TABLE[270-deg]);
	else// if ((deg>=270) && (deg<360))
		return FSIN_TABLE[deg-270];
}

float facos(float num){

	// return 0 if input is out of range
	if (num < -1 || num > 1) return 0;

	float ACOS = 0.0;

	//
	if (num == -1.0)		ACOS = PI;
	else if (num == 0.0)	ACOS = PIby2;
	else if (num == 1.0)	ACOS = 0;
	else{

		// if num<0.8, use polinomial
		// if num>=0.8, use table

		if (abs(num) <=0.8){

			float num2 = num*num;
			float num3 = num2*num;
			float num5 = num3*num2;
			float num7 = num5*num2;

			ACOS = PIby2 - num - 0.166667*num3 - 0.075*num5 - 0.044642*num7;

		}

		else{	// abs(num) > 0.8

			float findex = (abs(num)*1000.0 - 800.0)*0.25;// convert to index
			int index = FloatToInt(findex);

			float prop = findex-(float)index; // proportion of first index

			ACOS = prop*FACOS_TABLE[index]+(1-prop)*FACOS_TABLE[index+1];
			
			if (num < 0.0)
				ACOS = PI - ACOS;

		}
	}

	return ACOS;

}


float fatan2(float a, float b){
	// atan(a/b)

	// reflected about origin (angle can only be -90 to 90)

	if (a==0){
		if (b>=0)	return 0;
		else		return 0; // PI - PI
	}
	else if (a>0){
		if (b==0)		return PIby2;
		else			return atan(a/b);
	}
	else { // a<0
		if (b==0)		return -PIby2;
		else			return atan(a/b);
	}

}
