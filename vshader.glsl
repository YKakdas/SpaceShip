#version 150 


in vec4 vPosition;
in vec4 vNormal;
in vec4 AmbientProduct;
in vec4 DiffuseProduct;
in vec4 SpecularProduct;
out vec4 color;

uniform vec3 theta;
uniform vec4 TranslateVec;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;

void main()
{

	vec3 angle = radians(theta);
	vec3 angleCos = cos(angle);
	vec3 angleSin = sin(angle);
	
	
	mat4 rotateZ = mat4( angleCos.z, angleSin.z, 0.0, 0.0,
						-angleSin.z,  angleCos.z, 0.0, 0.0,
						0.0,  0.0, 1.0, 0.0,
						0.0,  0.0, 0.0, 1.0 );
	
	mat4 rotateX = mat4( 1.0, 0.0, 0.0, 0.0,
						0.0,  angleCos.x, angleSin.x, 0.0,
						0.0,  -angleSin.x, angleCos.x, 0.0,
						0.0,  0.0, 0.0, 1.0 );
						
	mat4 rotateY = mat4( angleCos.y, 0.0, -angleSin.y, 0.0,
						0.0,  1.0, 0.0, 0.0,
						angleSin.y,  0.0, angleCos.y, 0.0,
						0.0,  0.0, 0.0, 1.0 );
						
						
    // Transform vertex  position into eye coordinates
    vec3 pos = (ModelView * vPosition).xyz;
	
    vec3 L = normalize( (LightPosition).xyz - pos ); //assuming light position provided in camera coordinates
    vec3 E = normalize( -pos );
    vec3 H = normalize( L + E );

    // Transform vertex normal into eye coordinates
    vec3 N = normalize( ModelView*vNormal).xyz;

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks * SpecularProduct;
    
    if( dot(L, N) < 0.0 ) {
	specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 

	mat4 translate = mat4(1.0,0.0,0.0,0.0,
							0.0,1.0,0.0,0.0,
							0.0,0.0,1.0,0.0,
							TranslateVec.x,TranslateVec.y,TranslateVec.z,1.0);
    gl_Position =Projection * ModelView * translate * rotateY * vPosition;

    color = ambient + diffuse + specular;
    color.a = 1.0;
}
