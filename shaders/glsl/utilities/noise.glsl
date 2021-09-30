// Newb shader

// noise functions

// simple 1D noise - used in plants wave
float noise1D(float x){
    return cos(x)*cos(x*3.0)*cos(x*5.0) + 1.0;
}

// noise that works with mediump/lowp floats
// https://stackoverflow.com/questions/13540603/glsl-es-random-grainy-noise-with-fp16-limit
float rand(vec2 seed)
{
    vec2 theta_factor_a = vec2(0.9898, 0.233);
    vec2 theta_factor_b = vec2(12.0, 78.0);
    
    float theta_a = dot(seed.xy, theta_factor_a);
    float theta_b = dot(seed.xy, theta_factor_b);
    float theta_c = dot(seed.yx, theta_factor_a);
    float theta_d = dot(seed.yx, theta_factor_b);
    
    float value = cos(theta_a) * sin(theta_b) + sin(theta_c) * cos(theta_d);
    float temp = mod(197.0 * value, 1.0) + value;
    float part_a = mod(220.0 * temp, 1.0) + temp;
    float part_b = value * 0.5453;
    float part_c = cos(theta_a + theta_b) * 0.43758;

    return fract(part_a + part_b + part_c);
}

// interpolation of noise - used by rainy air blow
// see https://thebookofshaders.com/11/
float noise2D(vec2 p){

	vec2 ip = floor(p);
	vec2 u = fract(p);

	//u *= u*(3.0-2.0*u);
    u = 0.5-0.5*cos(u*3.14159265);
	
    float corner1 = rand(ip);
    float corner2 = rand(ip+vec2(1.0,0.0));
    float corner3 = rand(ip+vec2(0.0,1.0));
    float corner4 = rand(ip+vec2(1.0));

	float res = mix(mix(corner1,corner2,u.x),mix(corner3,corner4,u.x),u.y);

	return clamp(res*res,0.0,1.0);
}

