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
	//float expectedFogX = 0.034 + (0.09*FOG_CONTROL.y*FOG_CONTROL.y*FOG_CONTROL.y); // accuracy of 0.02
	//float expectedFogX = 0.168 - 0.136*exp(-FOG_CONTROL.y*FOG_CONTROL.y*FOG_CONTROL.y);	// accuracy of 0.015
	float expectedFogX = 0.029 + (0.09*FOG_CONTROL.y*FOG_CONTROL.y);	// accuracy of 0.015

	// nether wastes, basalt delta, crimson forest, wrapped forest, soul sand valley
	bool netherFogCtrl = (FOG_CONTROL.x<0.14  && abs(FOG_CONTROL.x-expectedFogX) < 0.02);
	bool netherFogCol = (FOG_COLOR.r+FOG_COLOR.g)>0.0;

	return (netherFogCtrl && netherFogCol);
}

bool detectUnderwater(){
	// underwater is also given a custom fog color in biomes_client.json to help in detection (unnecessary as FOG_CONTROL.x<0.001 is enough)
	return FOG_CONTROL.x<0.01 && FOG_COLOR.b>FOG_COLOR.r;
}

// needs more optimisation
float detectRain(bool underWater){

	// based on transition of FOG_CONTROL.xy

	// normal FOG_CONTROL.x varies with RENDER_DISTANCE
	// reverse plotted as 0.5 + 1.09/(k-0.8) where k is renderdistance in chunks
	float fogStart = 0.5 + (1.09/((RENDER_DISTANCE*0.0625)-0.8));

	// for MCPE 1.16 - mapped from screenshot
	vec2 start = vec2(fogStart,0.99);
	const vec2 end = vec2(0.24,0.7);

	if(!underWater && FOG_CONTROL.y < start.y && FOG_CONTROL.x < start.x && FOG_CONTROL.x > 0.1){

		//vec2 rainStep = smoothstep(start,end,FOG_CONTROL.xy);
		//float factor = rainStep.x*rainStep.y;

		float factor = 1.0-clamp((FOG_CONTROL.y-0.7)/(0.99-0.7),0.0,1.0);

		//ease in ease out using cos
		factor = 0.5-cos(factor*3.14159265)*0.5;

		//ease in ease out using pow
		//float facSqr = factor*factor;
		//factor = facSqr*(3.0 - 2.0*factor);

		factor *= 1.0-clamp((FOG_CONTROL.x-0.24)/(fogStart-0.24),0.0,1.0);

		return factor;
	}
	else{
		return 0.0;
	}
}


