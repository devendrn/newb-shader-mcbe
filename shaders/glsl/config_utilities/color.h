// Newb shader

/*""""""""""""""""""""""""""""""""""""""*/
/* COLOR CORRECTION */


// Type - Tone mapping type 
// 1 - Exponential
// 2 - Simple Reinhard
// 3 - Extended Reinhard (Default)
// 4 - ACES
#define TONEMAPPING_TYPE 3

// Toggle + Value - Exposure
//#define EXPOSURE 1.3

// Value - Contrast
#define CONTRAST 0.73

// Toggle + Value - Saturation
//#define SATURATION 1.4

// Toggle + Color - Tinting
//#define TINT vec3(1.0,0.75,0.5)


/*""""""""""""""""""""""""""""""""""""""*/


// Code starts here - Users shouldn't mess down here
// Color correction and tone mapping

// see https://64.github.io/tonemapping/

#if TONEMAPPING_TYPE==3
// extended reinhard tonemapping
vec3 tonemap(vec3 x){
	//float white = 4.0;
	//float white_scale = 1.0/(white*white);
	float white_scale = 0.063;

	x = (x*(1.0+(x*white_scale)))/(1.0+x);

	//x = (x*1.32)/(1.0+x);

	return x;
}

#elif TONEMAPPING_TYPE==4
// aces tone mapping
vec3 tonemap(vec3 x){
	x *= 0.85;
	const float a = 1.04;
	const float b = 0.03;
	const float c = 0.93;
	const float d = 0.56;
	const float e = 0.14;
	return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

#elif TONEMAPPING_TYPE==2
// simple reinhard tonemapping
vec3 tonemap(vec3 x){
	return x/(1.0 + x);
}

#elif TONEMAPPING_TYPE==1
// exponential tonemapping
vec3 tonemap(vec3 x){
	return 1.0-exp(-x*0.8);
}

#endif

vec3 colorCorrection(vec3 color){
	#ifdef EXPOSURE
		color *= EXPOSURE;
	#endif

	color = tonemap(color);

	// actually supposed to be gamma correction
	color = pow(color, vec3(CONTRAST));

	#ifdef SATURATION
		color = mix(vec3(dot(color,vec3(0.21, 0.71, 0.08))), color, SATURATION);
	#endif

	#ifdef TINT
		color *= TINT;
	#endif

	return color;
}

