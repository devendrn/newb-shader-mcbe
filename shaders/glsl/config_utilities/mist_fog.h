// copyright (c) Newb Shader

/*""""""""""""""""""""""""""""""""""""""*/
/* FOG & MIST */

// Type - Fog type
// 0 - Off
// 1 - Vanilla fog
// 2 - Smoother vanilla fog (Default)
#define FOG_TYPE 2

// Value - Density of mist
#define mist_density 0.15

/*""""""""""""""""""""""""""""""""""""""*/



// Code starts here - Users shouldn't mess down here

// mist & fog

vec4 renderMist(vec3 fog, float dist, float lit, float rain, bool nether, bool underwater, bool end){

	float density = mist_density;
	if(!(nether||end)){
		// increase density based on darkness
		density += density*(0.99-FOG_COLOR.b)*18.0;
	}

	vec4 mist;
	if(!nether){
		mist.rgb = fog*vec3(1.0,1.2-0.2*rain,1.4-0.4*rain);
	}
	else{
		mist.rgb = mix(fog*1.4,vec3(2.1,0.7,0.2), lit);
	}

	// exponential mist
	mist.a = 0.31-0.3*exp(-dist*dist*density);

	if(underwater){
		mist.rgb = fog;
		mist.a = 0.2+0.5*min(dist*dist,1.0);
	}

	return mist;
}

vec4 renderFog(vec3 fogColor, float len, bool nether){

#if FOG_TYPE > 0

	vec4 fog;
	if(!nether){fog.rgb = fogColor;}
	else{
		// inverse color correction
		fog.rgb = FOG_COLOR.rgb;
		fog.rgb = pow(fog.rgb,vec3(1.3888));
		vec3 w = vec3(0.7966);
		fog.rgb = fog.rgb*(w + fog.rgb)/(w + fog.rgb*(vec3(1.0) - w));
	}

	fog.a = clamp( (len -  FOG_CONTROL.x)/(FOG_CONTROL.y - FOG_CONTROL.x), 0.0, 1.0);

	#if FOG_TYPE > 1
		fog.a = (fog.a*fog.a)*(3.0-2.0*fog.a);
	#endif

	return fog;

#else

	return vec4(0.0);

#endif


}


