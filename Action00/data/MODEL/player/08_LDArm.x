xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 195;
 -16.47579;0.01748;-3.37208;,
 -0.01114;0.01748;-3.70719;,
 -0.01114;-2.60334;-2.62161;,
 -16.47579;-2.36640;-2.38465;,
 -0.01114;-3.68889;-0.00078;,
 -16.47579;-3.35380;-0.00078;,
 -0.01114;-2.60334;2.62004;,
 -16.47579;-2.36640;2.38308;,
 -0.01114;0.01748;3.70562;,
 -16.47579;0.01748;3.37052;,
 -0.01114;2.63831;2.62004;,
 -16.47579;2.40137;2.38308;,
 -0.01114;3.72391;-0.00078;,
 -16.47579;3.38880;-0.00078;,
 -0.01114;2.63831;-2.62161;,
 -16.47579;2.40137;-2.38465;,
 -0.01114;0.01748;-3.70719;,
 -16.47579;0.01748;-3.37208;,
 -16.47579;0.01748;-0.00078;,
 -16.47579;0.01748;-0.00078;,
 -16.47579;0.01748;-0.00078;,
 -16.47579;0.01748;-0.00078;,
 -16.47579;0.01748;-0.00078;,
 -16.47579;0.01748;-0.00078;,
 -16.47579;0.01748;-0.00078;,
 -16.47579;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.01114;0.01748;-0.00078;,
 -0.38944;-3.14216;4.66173;,
 -0.38944;0.01748;4.99586;,
 -7.23453;0.01748;4.99586;,
 -7.23453;-3.14216;4.66173;,
 -14.07961;0.01748;4.99586;,
 -14.07961;-3.14216;4.66173;,
 -0.38944;3.17715;4.66173;,
 -7.23453;3.17715;4.66173;,
 -14.07961;3.17715;4.66173;,
 -14.07961;-3.14216;4.66173;,
 -14.07961;0.01748;4.99586;,
 -14.57466;0.01748;4.18620;,
 -14.57466;-3.37067;3.85207;,
 -16.24011;0.01748;3.37654;,
 -16.24011;-4.13942;2.54310;,
 -14.07961;3.17715;4.66173;,
 -14.57466;3.40567;3.85207;,
 -16.24011;4.17444;2.54310;,
 -16.24011;-4.13942;2.54310;,
 -16.24011;0.01748;3.37654;,
 -7.23453;0.01748;3.37654;,
 -7.23453;-4.13942;2.54310;,
 1.77106;0.01748;3.37654;,
 1.77106;-4.13942;2.54310;,
 -16.24011;4.17444;2.54310;,
 -7.23453;4.17444;2.54310;,
 1.77106;4.17444;2.54310;,
 1.77106;-4.13942;2.54310;,
 1.77106;0.01748;3.37654;,
 0.10561;0.01748;4.18620;,
 0.10561;-3.37067;3.85207;,
 -0.38944;0.01748;4.99586;,
 -0.38944;-3.14216;4.66173;,
 1.77106;4.17444;2.54310;,
 0.10561;3.40567;3.85207;,
 -0.38944;3.17715;4.66173;,
 0.10561;-3.37067;3.85207;,
 -7.23453;-3.37067;3.85207;,
 -14.57466;-3.37067;3.85207;,
 -0.38944;-3.14216;4.66173;,
 -7.23453;-3.14216;4.66173;,
 -14.07961;-3.14216;4.66173;,
 0.10561;3.40567;3.85207;,
 -7.23453;3.40567;3.85207;,
 -14.57466;3.40567;3.85207;,
 -0.38944;3.17715;4.66173;,
 -7.23453;3.17715;4.66173;,
 -14.07961;3.17715;4.66173;,
 -9.79156;0.01748;-3.83888;,
 -8.16414;0.01748;-3.83888;,
 -8.16414;-2.69646;-2.71472;,
 -9.79156;-2.69646;-2.71472;,
 -8.16414;-3.82058;-0.00078;,
 -9.79156;-3.82058;-0.00078;,
 -8.16414;-2.69646;2.71315;,
 -9.79156;-2.69646;2.71315;,
 -8.16414;0.01748;3.83731;,
 -9.79156;0.01748;3.83731;,
 -8.16414;2.73143;2.71315;,
 -9.79156;2.73143;2.71315;,
 -8.16414;3.85560;-0.00078;,
 -9.79156;3.85560;-0.00078;,
 -8.16414;2.73143;-2.71472;,
 -9.79156;2.73143;-2.71472;,
 -8.16414;0.01748;-3.83888;,
 -9.79156;0.01748;-3.83888;,
 -9.79156;0.01748;-0.00078;,
 -9.79156;0.01748;-0.00078;,
 -9.79156;0.01748;-0.00078;,
 -9.79156;0.01748;-0.00078;,
 -9.79156;0.01748;-0.00078;,
 -9.79156;0.01748;-0.00078;,
 -9.79156;0.01748;-0.00078;,
 -9.79156;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -8.16414;0.01748;-0.00078;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;-0.00808;-1.44173;,
 -3.49818;-1.02614;-1.02004;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;-1.44787;-0.00197;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;-1.02614;1.01610;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;-0.00808;1.43779;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;1.01001;1.01610;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;1.43174;-0.00197;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;1.01001;-1.02004;,
 -3.78456;-0.00808;-0.00197;,
 -3.49818;-0.00808;-1.44173;,
 -2.68262;-0.00808;-2.66231;,
 -2.68262;-1.88920;-1.88311;,
 -2.68262;-2.66840;-0.00197;,
 -2.68262;-1.88920;1.87917;,
 -2.68262;-0.00808;2.65837;,
 -2.68262;1.87310;1.87917;,
 -2.68262;2.65230;-0.00197;,
 -2.68262;1.87310;-1.88311;,
 -2.68262;-0.00808;-2.66231;,
 -1.46204;-0.00808;-3.47786;,
 -1.46204;-2.46586;-2.45980;,
 -1.46204;-3.48393;-0.00197;,
 -1.46204;-2.46586;2.45586;,
 -1.46204;-0.00808;3.47394;,
 -1.46204;2.44974;2.45586;,
 -1.46204;3.46783;-0.00197;,
 -1.46204;2.44974;-2.45980;,
 -1.46204;-0.00808;-3.47786;,
 -0.02228;-0.00808;-3.76424;,
 -0.02228;-2.66840;-2.66231;,
 -0.02228;-3.77031;-0.00197;,
 -0.02228;-2.66840;2.65837;,
 -0.02228;-0.00808;3.76032;,
 -0.02228;2.65230;2.65837;,
 -0.02228;3.75420;-0.00197;,
 -0.02228;2.65230;-2.66231;,
 -0.02228;-0.00808;-3.76424;,
 1.41749;-0.00808;-3.47786;,
 1.41749;-2.46586;-2.45980;,
 1.41749;-3.48393;-0.00197;,
 1.41749;-2.46586;2.45586;,
 1.41749;-0.00808;3.47394;,
 1.41749;2.44974;2.45586;,
 1.41749;3.46783;-0.00197;,
 1.41749;2.44974;-2.45980;,
 1.41749;-0.00808;-3.47786;,
 2.63807;-0.00808;-2.66231;,
 2.63807;-1.88920;-1.88311;,
 2.63807;-2.66840;-0.00197;,
 2.63807;-1.88920;1.87917;,
 2.63807;-0.00808;2.65837;,
 2.63807;1.87310;1.87917;,
 2.63807;2.65230;-0.00197;,
 2.63807;1.87310;-1.88311;,
 2.63807;-0.00808;-2.66231;,
 3.45362;-0.00808;-1.44173;,
 3.45362;-1.02614;-1.02004;,
 3.45362;-1.44787;-0.00197;,
 3.45362;-1.02614;1.01610;,
 3.45362;-0.00808;1.43779;,
 3.45362;1.01001;1.01610;,
 3.45362;1.43174;-0.00197;,
 3.45362;1.01001;-1.02004;,
 3.45362;-0.00808;-1.44173;,
 3.74001;-0.00808;-0.00197;,
 3.74001;-0.00808;-0.00197;,
 3.74001;-0.00808;-0.00197;,
 3.74001;-0.00808;-0.00197;,
 3.74001;-0.00808;-0.00197;,
 3.74001;-0.00808;-0.00197;,
 3.74001;-0.00808;-0.00197;,
 3.74001;-0.00808;-0.00197;;
 
 136;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 3;18,0,3;,
 3;19,3,5;,
 3;20,5,7;,
 3;21,7,9;,
 3;22,9,11;,
 3;23,11,13;,
 3;24,13,15;,
 3;25,15,17;,
 3;26,2,1;,
 3;27,4,2;,
 3;28,6,4;,
 3;29,8,6;,
 3;30,10,8;,
 3;31,12,10;,
 3;32,14,12;,
 3;33,16,14;,
 4;34,35,36,37;,
 4;37,36,38,39;,
 4;35,40,41,36;,
 4;36,41,42,38;,
 4;43,44,45,46;,
 4;46,45,47,48;,
 4;44,49,50,45;,
 4;45,50,51,47;,
 4;52,53,54,55;,
 4;55,54,56,57;,
 4;53,58,59,54;,
 4;54,59,60,56;,
 4;61,62,63,64;,
 4;64,63,65,66;,
 4;62,67,68,63;,
 4;63,68,69,65;,
 4;61,70,71,55;,
 4;55,71,72,48;,
 4;70,73,74,71;,
 4;71,74,75,72;,
 4;76,67,59,77;,
 4;77,59,51,78;,
 4;79,76,77,80;,
 4;80,77,78,81;,
 4;82,83,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,96,97;,
 4;97,96,98,99;,
 3;100,82,85;,
 3;101,85,87;,
 3;102,87,89;,
 3;103,89,91;,
 3;104,91,93;,
 3;105,93,95;,
 3;106,95,97;,
 3;107,97,99;,
 3;108,84,83;,
 3;109,86,84;,
 3;110,88,86;,
 3;111,90,88;,
 3;112,92,90;,
 3;113,94,92;,
 3;114,96,94;,
 3;115,98,96;,
 3;116,117,118;,
 3;119,118,120;,
 3;121,120,122;,
 3;123,122,124;,
 3;125,124,126;,
 3;127,126,128;,
 3;129,128,130;,
 3;131,130,132;,
 4;117,133,134,118;,
 4;118,134,135,120;,
 4;120,135,136,122;,
 4;122,136,137,124;,
 4;124,137,138,126;,
 4;126,138,139,128;,
 4;128,139,140,130;,
 4;130,140,141,132;,
 4;133,142,143,134;,
 4;134,143,144,135;,
 4;135,144,145,136;,
 4;136,145,146,137;,
 4;137,146,147,138;,
 4;138,147,148,139;,
 4;139,148,149,140;,
 4;140,149,150,141;,
 4;142,151,152,143;,
 4;143,152,153,144;,
 4;144,153,154,145;,
 4;145,154,155,146;,
 4;146,155,156,147;,
 4;147,156,157,148;,
 4;148,157,158,149;,
 4;149,158,159,150;,
 4;151,160,161,152;,
 4;152,161,162,153;,
 4;153,162,163,154;,
 4;154,163,164,155;,
 4;155,164,165,156;,
 4;156,165,166,157;,
 4;157,166,167,158;,
 4;158,167,168,159;,
 4;160,169,170,161;,
 4;161,170,171,162;,
 4;162,171,172,163;,
 4;163,172,173,164;,
 4;164,173,174,165;,
 4;165,174,175,166;,
 4;166,175,176,167;,
 4;167,176,177,168;,
 4;169,178,179,170;,
 4;170,179,180,171;,
 4;171,180,181,172;,
 4;172,181,182,173;,
 4;173,182,183,174;,
 4;174,183,184,175;,
 4;175,184,185,176;,
 4;176,185,186,177;,
 3;178,187,179;,
 3;179,188,180;,
 3;180,189,181;,
 3;181,190,182;,
 3;182,191,183;,
 3;183,192,184;,
 3;184,193,185;,
 3;185,194,186;;
 
 MeshMaterialList {
  7;
  136;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\0.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.088000;0.112800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.649600;0.649600;0.649600;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.724800;0.000000;0.034400;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.207200;0.207200;0.207200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  117;
  -1.000000;0.000000;0.000000;,
  -0.020349;0.000000;-0.999793;,
  -0.020348;-0.706964;-0.706957;,
  -0.020348;-0.999793;0.000001;,
  -0.020348;-0.706964;0.706957;,
  -0.020349;0.000000;0.999793;,
  -0.020348;0.706959;0.706961;,
  -0.020348;0.999793;0.000001;,
  -0.020349;0.706959;-0.706962;,
  1.000000;0.000000;0.000000;,
  0.485280;-0.090878;0.869623;,
  0.000000;-0.105163;0.994455;,
  0.487297;-0.000000;0.873237;,
  0.000000;-0.000000;1.000000;,
  0.485280;0.090877;0.869623;,
  0.000000;0.105162;0.994455;,
  -0.485280;-0.090878;0.869623;,
  -0.695411;-0.092598;0.712622;,
  -0.487297;-0.000000;0.873237;,
  -0.698411;-0.000000;0.715697;,
  -0.485280;0.090877;0.869623;,
  -0.695411;0.092597;0.712622;,
  -0.285079;-0.562663;0.775977;,
  0.000000;0.196583;-0.980487;,
  -0.504699;-0.000001;0.863296;,
  0.000000;0.000001;-1.000000;,
  -0.285078;0.562657;0.775982;,
  0.000000;-0.196581;-0.980488;,
  0.000000;0.196583;-0.980487;,
  0.695411;-0.092598;0.712622;,
  0.000000;0.000001;-1.000000;,
  0.698411;-0.000000;0.715697;,
  0.000000;-0.196581;-0.980488;,
  0.695411;0.092597;0.712622;,
  0.000000;-0.919868;0.392228;,
  0.000000;0.919865;0.392235;,
  0.000000;0.196583;-0.980487;,
  0.000000;-0.196581;-0.980488;,
  0.285079;-0.562663;0.775977;,
  0.504699;-0.000001;0.863296;,
  0.285078;0.562657;0.775982;,
  0.000000;-0.919868;0.392228;,
  0.000000;-0.862289;0.506416;,
  0.000000;-0.919868;0.392228;,
  0.000000;-0.962403;0.271625;,
  0.000000;-0.962403;0.271625;,
  0.000000;0.919865;0.392235;,
  0.000000;0.862282;0.506429;,
  0.000000;0.962403;0.271626;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.707111;-0.707103;,
  0.000000;-1.000000;0.000001;,
  0.000000;-0.707111;0.707103;,
  0.000000;0.000000;1.000000;,
  0.000000;0.707105;0.707108;,
  0.000000;1.000000;0.000001;,
  0.000000;0.707105;-0.707108;,
  1.000000;0.000000;0.000000;,
  -1.000000;-0.000001;0.000000;,
  -0.924737;-0.000002;-0.380608;,
  -0.924736;-0.269129;-0.269134;,
  -0.924737;-0.380608;0.000000;,
  -0.924736;-0.269129;0.269134;,
  -0.924737;-0.000002;0.380607;,
  -0.924738;0.269125;0.269133;,
  -0.924739;0.380603;-0.000000;,
  -0.924737;0.269126;-0.269133;,
  -0.709228;-0.000003;-0.704979;,
  -0.709224;-0.498499;-0.498499;,
  -0.709222;-0.704986;0.000000;,
  -0.709224;-0.498499;0.498498;,
  -0.709229;-0.000003;0.704978;,
  -0.709225;0.498495;0.498500;,
  -0.709222;0.704985;-0.000000;,
  -0.709224;0.498496;-0.498501;,
  -0.384550;-0.000002;-0.923104;,
  -0.384548;-0.652737;-0.652731;,
  -0.384545;-0.923106;-0.000000;,
  -0.384547;-0.652737;0.652731;,
  -0.384551;-0.000003;0.923104;,
  -0.384548;0.652734;0.652734;,
  -0.384546;0.923106;-0.000000;,
  -0.384547;0.652734;-0.652734;,
  -0.000001;-0.000003;-1.000000;,
  -0.000001;-0.707110;-0.707104;,
  -0.000001;-1.000000;0.000000;,
  -0.000001;-0.707111;0.707103;,
  -0.000001;-0.000003;1.000000;,
  -0.000001;0.707107;0.707107;,
  -0.000000;1.000000;-0.000000;,
  -0.000001;0.707106;-0.707107;,
  0.384549;-0.000002;-0.923104;,
  0.384547;-0.652737;-0.652731;,
  0.384544;-0.923107;0.000000;,
  0.384547;-0.652737;0.652731;,
  0.384550;-0.000003;0.923104;,
  0.384548;0.652734;0.652734;,
  0.384546;0.923106;-0.000000;,
  0.384548;0.652734;-0.652734;,
  0.709230;-0.000002;-0.704977;,
  0.709226;-0.498497;-0.498497;,
  0.709224;-0.704984;0.000000;,
  0.709226;-0.498498;0.498497;,
  0.709230;-0.000003;0.704977;,
  0.709226;0.498495;0.498499;,
  0.709224;0.704984;-0.000000;,
  0.709225;0.498495;-0.498500;,
  0.924736;-0.000002;-0.380610;,
  0.924735;-0.269131;-0.269135;,
  0.924736;-0.380610;0.000000;,
  0.924735;-0.269131;0.269136;,
  0.924736;-0.000002;0.380610;,
  0.924736;0.269127;0.269135;,
  0.924737;0.380606;0.000000;,
  0.924736;0.269127;-0.269135;,
  1.000000;-0.000001;0.000000;;
  136;
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,1,1;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,12,13,11;,
  4;11,13,18,16;,
  4;12,14,15,13;,
  4;13,15,20,18;,
  4;16,18,19,17;,
  4;17,19,24,22;,
  4;18,20,21,19;,
  4;19,21,26,24;,
  4;36,25,25,23;,
  4;23,25,30,28;,
  4;25,37,27,25;,
  4;25,27,32,30;,
  4;38,39,31,29;,
  4;29,31,12,10;,
  4;39,40,33,31;,
  4;31,33,14,12;,
  4;38,41,34,42;,
  4;42,34,43,22;,
  4;41,44,44,34;,
  4;34,44,45,43;,
  4;46,40,47,35;,
  4;35,47,26,35;,
  4;48,46,35,48;,
  4;48,35,35,48;,
  4;50,50,51,51;,
  4;51,51,52,52;,
  4;52,52,53,53;,
  4;53,53,54,54;,
  4;54,54,55,55;,
  4;55,55,56,56;,
  4;56,56,57,57;,
  4;57,57,50,50;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;59,60,61;,
  3;59,61,62;,
  3;59,62,63;,
  3;59,63,64;,
  3;59,64,65;,
  3;59,65,66;,
  3;59,66,67;,
  3;59,67,60;,
  4;60,68,69,61;,
  4;61,69,70,62;,
  4;62,70,71,63;,
  4;63,71,72,64;,
  4;64,72,73,65;,
  4;65,73,74,66;,
  4;66,74,75,67;,
  4;67,75,68,60;,
  4;68,76,77,69;,
  4;69,77,78,70;,
  4;70,78,79,71;,
  4;71,79,80,72;,
  4;72,80,81,73;,
  4;73,81,82,74;,
  4;74,82,83,75;,
  4;75,83,76,68;,
  4;76,84,85,77;,
  4;77,85,86,78;,
  4;78,86,87,79;,
  4;79,87,88,80;,
  4;80,88,89,81;,
  4;81,89,90,82;,
  4;82,90,91,83;,
  4;83,91,84,76;,
  4;84,92,93,85;,
  4;85,93,94,86;,
  4;86,94,95,87;,
  4;87,95,96,88;,
  4;88,96,97,89;,
  4;89,97,98,90;,
  4;90,98,99,91;,
  4;91,99,92,84;,
  4;92,100,101,93;,
  4;93,101,102,94;,
  4;94,102,103,95;,
  4;95,103,104,96;,
  4;96,104,105,97;,
  4;97,105,106,98;,
  4;98,106,107,99;,
  4;99,107,100,92;,
  4;100,108,109,101;,
  4;101,109,110,102;,
  4;102,110,111,103;,
  4;103,111,112,104;,
  4;104,112,113,105;,
  4;105,113,114,106;,
  4;106,114,115,107;,
  4;107,115,108,100;,
  3;108,116,109;,
  3;109,116,110;,
  3;110,116,111;,
  3;111,116,112;,
  3;112,116,113;,
  3;113,116,114;,
  3;114,116,115;,
  3;115,116,108;;
 }
 MeshTextureCoords {
  195;
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
