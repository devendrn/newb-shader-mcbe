// Newb shader

// noise functions

// simple 1D noise - used in plants wave
float noise1D(float x){
	return cos(x)*cos(x*3.0)*cos(x*5.0) + 1.0;
}

// hash function for noise (for highp only)
highp float rand(highp vec2 n){
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

// hash function (lowp supported)
//float rand(vec2 n){
//	return fract((sin(n.x+n.y)+sin((n.x-n.y)))*53.968);
//}

// interpolation of noise - used by rainy air blow
// see https://thebookofshaders.com/11/
float noise2D(vec2 p){

	vec2 p0 = floor(p);
	vec2 u = p-p0;

	u *= u*(3.0-2.0*u);
	vec2 v = 1.0 - u;

	float c1 = rand(p0);
	float c2 = rand(p0+vec2(1.0,0.0));
	float c3 = rand(p0+vec2(0.0,1.0));
	float c4 = rand(p0+vec2(1.0));

	float n = v.y*(c1*v.x+c2*u.x) + u.y*(c3*v.x+c4*u.x);

	return n*n;
}

