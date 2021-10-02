// Newb shader

/*""""""""""""""""""""""""""""""""""""""*/
/* SMOOTH CLOUDS */

//️ Value - Number of clouds (not implemented)
//#define cloud_frequency 0.7

// Cloud size when raining (0-1)
#define rain_cloud_size 0.9

// Normal cloud size (0-1)
#define normal_cloud_size 0.3

// Value - Cloud map size (0-100)
#define cloud_noise_size 36.0

// Value - Cloud movement speed
#define cloud_speed 0.04

// Value - Cloud shadow intensity (0-1)
#define cloud_shadow 0.54

// Value - Cloud transparency (0-1)
#define cloud_alpha 1.0

/*""""""""""""""""""""""""""""""""""""""*/


/*""""""""""""""""""""""""""""""""""""""*/
/* AURORA EFFECT */

//️ Toggle - Enable aurora effect for night sky
#define ENABLE_AURORA

//️ Value - Aurora borealis brightness
#define aurora_intensity 1.0

/*""""""""""""""""""""""""""""""""""""""*/



// Code starts here - Users shouldn't mess down here
// Clouds noise

const vec2 cloud_size = vec2(0.7,1.0)/cloud_noise_size;

const float start_rain = 1.0-rain_cloud_size;
const float start_normal = 1.0-normal_cloud_size;

// modified rand for cloud noise
float rand01(vec2 seed,float start){
	float result = rand(seed);
	result = clamp((result-start)*3.4,0.0,1.0);
	return result*result;
}

// 2D cloud noise - used by clouds
float cloudNoise2D(vec2 p, highp float t, float rain){

	t *= cloud_speed;

	// start threshold - for bigger clouds during rain
	float start = start_normal + (normal_cloud_size)*(0.1+0.1*sin(t + p.y*0.3));
	start = mix(start,start_rain,rain);

	p += vec2(t);
	p.x += sin(p.y*0.4 + t);

	vec2 ip = floor(p);
	vec2 u = fract(p);

	//u *= u*(3.0-2.0*u);
	u = 0.5-0.5*cos(u*3.14159265);

	float corner1 = rand01(ip,start);
	float corner2 = rand01(ip+vec2(1.0,0.0),start);
	float corner3 = rand01(ip+vec2(0.0,1.0),start);
	float corner4 = rand01(ip+vec2(1.0),start);

	return mix(mix(corner1,corner2,u.x),mix(corner3,corner4,u.x),u.y);
}

// simple cloud
vec4 renderClouds(vec4 color, vec2 uv, highp float t, float rain){

	float cloudAlpha = cloudNoise2D(uv,t,rain)*0.8;
	float cloudShadow = cloudNoise2D(uv,(t+0.16),rain)*0.2;

	cloudAlpha = max(cloudAlpha-cloudShadow,0.0);

	// rainy clouds color
	color.rgb = mix(color.rgb,vec3(0.7),rain*0.5);

	// highlight at edge
	color.rgb += vec3(0.6,0.6,1.0)*(0.2-cloudShadow);

	// cloud shadow
	color.rgb *= (1.0-cloudShadow*3.0*cloud_shadow);

	return vec4(color.rgb,cloudAlpha);
}

// simple northern night sky effect
vec4 renderAurora(vec2 uv, highp float t, float rain){
	float auroraCurves = sin(uv.x*0.09 + 0.07*t) + 0.3*sin(uv.x*0.5 + 0.08*t) + 0.03*sin((uv.x+uv.y)*3.0 + 0.2*t);
	float auroraBase = uv.y*0.4 + 2.0*auroraCurves;
	float auroraFlow = 0.5+0.5*sin(uv.x*0.3 + 0.07*t + 0.7*sin(auroraBase*0.9) );

	float auroraCol = sin(uv.y*0.06 + 0.07*t);
	auroraCol = abs(auroraCol*auroraCol*auroraCol);

	float aurora = sin(auroraBase)*sin(auroraBase*0.3);
	aurora = abs(aurora*auroraFlow);

	return vec4(
		0.0,
		(1.0-auroraCol)*aurora,
		auroraCol*aurora,
		aurora*aurora*(0.5-0.5*rain) )*aurora_intensity;
}
