// Newb shader

/*""""""""""""""""""""""""""""""""""""""*/
/* SKY */

// color - Night sky color
const vec3 nightSkyCol = vec3(0.01,0.06,0.1);

// color - Sky base color
const vec3 skyBaseCol = vec3(0.15,0.45,1.0);

// value - Day sky clarity (0-1)
const float daySkyClarity = 0.3;

// color - Sunrise base color
const vec3 horizonBaseCol = vec3(1.0,0.25,0.2);

// color - Sunrise edge color
const vec3 horizonEdgeCol = vec3(1.0,0.4,0.2);

// color - Underwater fog color
const vec3 underwaterBaseCol = vec3(0.0,0.6,1.0);

/*""""""""""""""""""""""""""""""""""""""*/


// Code starts here - Users shouldn't mess down here
// functions related to sky

// uniform FOG_COLOR is used

const vec3 horizonEdgeAbsCol = 1.0-horizonEdgeCol;

// sky colors - needs more tweaking

vec3 getUnderwaterCol(){
	return underwaterBaseCol*FOG_COLOR.b;
}

vec3 getZenithCol(float rainFactor){

	// value needs tweaking
	float val = max(FOG_COLOR.r*0.6,max(FOG_COLOR.g,FOG_COLOR.b));

	// zenith color
	vec3 zenithCol = 1.1*val*val*skyBaseCol;
	zenithCol += nightSkyCol*(0.4-0.4*FOG_COLOR.b);

	// rain sky
	float brightness = min(FOG_COLOR.g,0.26);
	brightness *= brightness*13.2;
	zenithCol = mix(zenithCol*(1.0+0.5*rainFactor),vec3(0.85,0.9,1.0)*brightness,rainFactor);

	return zenithCol;
}

vec3 getHorizonCol(float rainFactor){

	// value needs tweaking
	float val = max(FOG_COLOR.r*0.65,max(FOG_COLOR.g*1.1,FOG_COLOR.b));

	float sun = max(FOG_COLOR.r-FOG_COLOR.b,0.0);

	// horizon color
	vec3 horizonCol = horizonBaseCol*((val*val + sun)*1.7);

	horizonCol += nightSkyCol;

	horizonCol = mix(
		horizonCol,
		2.1*val*mix(vec3(0.7,1.0,0.9),skyBaseCol,daySkyClarity),
		val*val);

	// rain horizon
	float brightness = min(FOG_COLOR.g,0.26);
	brightness *= brightness*19.6;
	horizonCol = mix(horizonCol,vec3(brightness),rainFactor);

	return horizonCol;
}

vec3 getHorizonEdgeCol(vec3 horizonCol, float rainFactor){
	float val = (1.1-FOG_COLOR.b)*FOG_COLOR.g*2.1;
	val *= 1.0-rainFactor;

	vec3 tint = vec3(1.0)-val*horizonEdgeAbsCol;
	return horizonCol*tint;
}


// sunlight tinting
vec3 sunLightTint(vec3 night_color,vec3 morning_color,vec3 day_color,float dayFactor,float rain){

	float tintFactor = FOG_COLOR.g + 0.1*FOG_COLOR.r;
	float morning = clamp((tintFactor-0.37)/0.45,0.0,1.0);
	float night = clamp((tintFactor-0.05)*3.125,0.0,1.0);

	// morning tint during rain fix
	morning = min(morning + rain*4.5,1.0);
	night = night*(1.0-rain);

	return mix(
		mix(night_color,morning_color,night),
		mix(mix(morning_color.rgb,morning_color.bgr,min(rain*5.0,1.0)),day_color,morning),
		dayFactor);
}

// Colors end


// 1D sky with three color gradient
// A copy of this is in sky.fragment, make changes there aswell
vec3 renderSky(vec3 reddishTint, vec3 horizonColor, vec3 zenithColor, float h){

//h = h+0.04;
//if(h > 0.0){h /= 1.04;}
//else{h /= -0.96;}

	h = 1.0-h*h;

	float hsq = h*h;

	// gradient 1  h^16
	// gradient 2  h^8 mix h^2
	float gradient1 = hsq*hsq*hsq*hsq;
	float gradient2 = 0.5*(gradient1 + hsq);
	gradient1 *= gradient1;

	horizonColor = mix(horizonColor, reddishTint, gradient1);
	return mix(zenithColor,horizonColor, gradient2 );

}


