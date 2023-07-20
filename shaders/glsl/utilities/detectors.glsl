// Newb shader

// uniforms FOG_COLOR, FOG_CONTROL are used

bool detectEnd(){
	// end is given a custom fog color in biomes_client.json to help in detection
	// dark color (issue- rain transition when entering end)
	return FOG_COLOR.r==FOG_COLOR.b && FOG_COLOR.r > 0.1  && FOG_COLOR.g < FOG_COLOR.r*0.4;
}

bool detectNether(){
	// FOG_CONTROL x and y varies with renderdistance
	// x range (0.03,0.14) 

	// reverse plotted relation (5,6,7,8,9,11,12,20,96 chunks data) with an accuracy of 0.02
	float expectedFogX = 0.029 + (0.09*FOG_CONTROL.y*FOG_CONTROL.y);	// accuracy of 0.015

	// nether wastes, basalt delta, crimson forest, wrapped forest, soul sand valley
	bool netherFogCtrl = (FOG_CONTROL.x<0.14  && abs(FOG_CONTROL.x-expectedFogX) < 0.02);
	bool netherFogCol = (FOG_COLOR.r+FOG_COLOR.g)>0.0;

	// consider underlava as nether
	bool underLava = FOG_CONTROL.x==0.0 && FOG_COLOR.b==0.0 && FOG_COLOR.g<0.18 && FOG_COLOR.r-FOG_COLOR.g>0.1;

	return (netherFogCtrl && netherFogCol) || underLava;
}

bool detectUnderwater(){
	return FOG_CONTROL.x<0.001 && max(FOG_COLOR.b,FOG_COLOR.g)>FOG_COLOR.r;
}


float detectRain(){
	// FOG_CONTROL values when clear/rain
	// clear FOG_CONTROL.x varies with RENDER_DISTANCE
	// reverse plotted (low accuracy) as 0.5 + 1.09/(k-0.8) where k is renderdistance in chunks
	// remaining values are equal to those specified in json file
	vec2 start = vec2(0.5 + (1.09/((RENDER_DISTANCE*0.0625)-0.8)),0.99);
	const vec2 end = vec2(0.2305,0.7005);

	vec2 factor = clamp((start-FOG_CONTROL)/(start-end),vec2(0.0),vec2(1.0));

	// ease in ease out
	factor.y = factor.y*factor.y*(3.0 - 2.0*factor.y);

	return factor.x*factor.y;
}


