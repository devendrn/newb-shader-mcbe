// Newb shader

/*""""""""""""""""""""""""""""""""""""""*/
/* COLOR CORRECTION */


// Type - Tone mapping type 
// 1 - Exponential
// 2 - Simple Reinhard
// 3 - Extended Reinhard (Default)
// 4 - Uncharted 2
#define TONEMAPPING_TYPE 3

// Toggle - Increase exposure based on fog color
//#define ADAPTIVE_BRIGHTNESS

// Toggle + Value - Exposure
//#define EXPOSURE 1.3

// Value - Contrast
#define CONTRAST 0.73

// Toggle + Value - Saturation
//#define SATURATION 1.4

// Toggle + Color - Tinting
//#define TINT vec3(1.0,0.8,0.4)


/*""""""""""""""""""""""""""""""""""""""*/


// Code starts here - Users shouldn't mess down here
// Color correction and tone mapping

#ifdef ADAPTIVE_BRIGHTNESS
	uniform vec4 FOG_COLOR;
#endif

// see https://64.github.io/tonemapping/

#if TONEMAPPING_TYPE==3
// extended reinhard tonemapping
vec3 tonemap(vec3 color){
	//float white = 4.0;
	//float white_scale = 1.0/(white*white);
	float white_scale = 0.063;

	color = (color*(1.0+(color*white_scale)))/(1.0+color);

	//color = (color*1.32)/(1.0+color);

	return color;
}

#elif TONEMAPPING_TYPE==4
// uncharted 2 tone mapping
vec3 tonemap(vec3 color){
	float A = 0.15;
	float B = 0.50;
	//float C = 0.10;
	//float D = 0.20;
	//float E = 0.02;
	//float F = 0.30;

	float exposure = 2.0;
	vec3 x = color*exposure;

	//color = ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
	color = ((x*(A*x+0.05)+0.004)/(x*(A*x+B)+0.06))-0.06666667;

	//float W = 11.2;
	//float white_scale = 1.0/(((W*(A*W+C*B)+D*E)/(W*(A*W+B)+D*F))-E/F);
	float white_scale = 1.37906425;

	return color*white_scale;
}

#elif TONEMAPPING_TYPE==2
// simple reinhard tonemapping
vec3 tonemap(vec3 color){
	return color/(1.0 + color);
}

#elif TONEMAPPING_TYPE==1
// exponential tonemapping
vec3 tonemap(vec3 color){
	return 1.0-exp(-color*0.8);
}

#endif

vec3 colorCorrection(vec3 color){
	#ifdef EXPOSURE
		color *= EXPOSURE;
	#endif

	#ifdef ADAPTIVE_BRIGHTNESS
		color *= 2.0 - dot(FOG_COLOR.rgb,vec3(0.35,0.25,0.5));
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

