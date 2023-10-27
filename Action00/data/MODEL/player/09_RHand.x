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
 206;
 10.91555;0.00847;0.01339;,
 10.37816;-0.72405;2.04606;,
 10.37816;-1.02746;0.01339;,
 10.91555;0.00847;0.01339;,
 10.37816;0.00847;2.38298;,
 10.91555;0.00847;0.01339;,
 10.37816;0.74097;2.04606;,
 10.91555;0.00847;0.01339;,
 10.37816;1.04438;0.01339;,
 10.91555;0.00847;0.01339;,
 10.37816;0.74097;-2.07781;,
 10.91555;0.00847;0.01339;,
 10.37816;0.00847;-2.39674;,
 10.91555;0.00847;0.01339;,
 10.37816;-0.72405;-2.07781;,
 10.91555;0.00847;0.01339;,
 10.37816;-1.02746;0.01339;,
 9.00131;-1.34504;2.73563;,
 9.00131;-1.90569;0.01339;,
 9.00131;0.00847;3.35817;,
 9.00131;1.36199;2.73563;,
 9.00131;1.92263;0.01339;,
 9.00131;1.36199;-2.73056;,
 9.00131;0.00847;-3.31987;,
 9.00131;-1.34504;-2.73056;,
 9.00131;-1.90569;0.01339;,
 6.94066;-1.75994;3.19638;,
 6.94066;-2.49245;0.01339;,
 6.94066;0.00847;4.00977;,
 6.94066;1.77693;3.19638;,
 6.94066;2.50940;0.01339;,
 6.94066;1.77693;-3.16671;,
 6.94066;0.00847;-3.93669;,
 6.94066;-1.75994;-3.16671;,
 6.94066;-2.49245;0.01339;,
 4.50999;-1.90569;3.35817;,
 4.50999;-2.69856;0.01339;,
 4.50999;0.00847;4.23858;,
 4.50999;1.92263;3.35817;,
 4.50999;2.71548;0.01339;,
 4.50999;1.92263;-3.31987;,
 4.50999;0.00847;-4.15328;,
 4.50999;-1.90566;-3.31987;,
 4.50999;-2.69856;0.01339;,
 2.07930;-1.75994;3.19638;,
 2.07930;-2.49245;0.01339;,
 2.07930;0.00847;4.00977;,
 2.07930;1.77693;3.19638;,
 2.07930;2.50940;0.01339;,
 2.07930;1.77693;-3.16671;,
 2.07930;0.00847;-3.93669;,
 2.07930;-1.75994;-3.16671;,
 2.07930;-2.49245;0.01339;,
 0.01868;-1.34504;2.73563;,
 0.01868;-1.90569;0.01339;,
 0.01868;0.00847;3.35817;,
 0.01868;1.36199;2.73563;,
 0.01868;1.92263;0.01339;,
 0.01868;1.36199;-2.73056;,
 0.01868;0.00847;-3.31987;,
 0.01868;-1.34504;-2.73056;,
 0.01868;-1.90569;0.01339;,
 -1.35820;-0.72405;2.04606;,
 -1.35820;-1.02746;0.01339;,
 -1.35820;0.00847;2.38298;,
 -1.35820;0.74097;2.04606;,
 -1.35820;1.04438;0.01339;,
 -1.35820;0.74097;-2.07781;,
 -1.35820;0.00847;-2.39674;,
 -1.35820;-0.72405;-2.07781;,
 -1.35820;-1.02746;0.01339;,
 -1.84169;0.00847;0.01339;,
 -1.84169;0.00847;0.01339;,
 -1.84169;0.00847;0.01339;,
 -1.84169;0.00847;0.01339;,
 -1.84169;0.00847;0.01339;,
 -1.84169;0.00847;0.01339;,
 -1.84169;0.00847;0.01339;,
 -1.84169;0.00847;0.01339;,
 5.87980;-0.09666;-4.23597;,
 5.63973;-0.95010;-4.77331;,
 5.64328;-0.09666;-4.89629;,
 5.87980;-0.09666;-4.23597;,
 5.63113;-1.09155;-4.47641;,
 5.87980;-0.09666;-4.23597;,
 5.62250;-0.95010;-4.17952;,
 5.87980;-0.09666;-4.23597;,
 5.61897;-0.09666;-4.05654;,
 5.87980;-0.09666;-4.23597;,
 5.62250;0.78137;-4.17952;,
 5.87980;-0.09666;-4.23597;,
 5.63113;0.91523;-4.47641;,
 5.87980;-0.09666;-4.23597;,
 5.63973;0.78137;-4.77331;,
 5.87980;-0.09666;-4.23597;,
 5.64328;-0.09666;-4.89629;,
 4.79001;-1.23960;-5.33607;,
 4.79659;-0.09666;-5.56331;,
 4.77417;-1.50102;-4.78748;,
 4.75827;-1.23960;-4.23888;,
 4.75172;-0.09666;-4.01164;,
 4.75827;1.05540;-4.23888;,
 4.77417;1.30286;-4.78748;,
 4.79001;1.05540;-5.33607;,
 4.79659;-0.09666;-5.56331;,
 3.05345;-1.43308;-5.66896;,
 2.87954;-0.09666;-5.92083;,
 3.47325;-1.77458;-5.06089;,
 3.59645;-1.43308;-4.27041;,
 3.57993;-0.09666;-3.94981;,
 3.59645;1.23857;-4.27041;,
 3.47325;1.56184;-5.06089;,
 3.05345;1.23857;-5.66896;,
 2.87954;-0.09666;-5.92083;,
 1.73542;-1.50102;-4.99323;,
 1.54720;-0.09666;-5.26585;,
 2.18983;-1.87065;-4.33505;,
 2.64424;-1.50102;-3.67688;,
 2.83247;-0.09666;-3.40426;,
 2.64424;1.30286;-3.67688;,
 2.18983;1.65276;-4.33505;,
 1.73542;1.30286;-4.99323;,
 1.54720;-0.09666;-5.26585;,
 0.48658;-1.43308;-4.21729;,
 0.31270;-0.09666;-4.46915;,
 0.90642;-1.77458;-3.60922;,
 1.32622;-1.43308;-3.00115;,
 1.50013;-0.09666;-2.74928;,
 1.32622;1.23857;-3.00115;,
 0.90642;1.56184;-3.60922;,
 0.48658;1.23857;-4.21728;,
 0.31270;-0.09666;-4.46915;,
 -0.50291;-1.23960;-3.45929;,
 -0.63603;-0.09666;-3.65206;,
 -0.18162;-1.50102;-2.99389;,
 0.13969;-1.23960;-2.52849;,
 0.27280;-0.09666;-2.33572;,
 0.13969;1.05540;-2.52849;,
 -0.18162;1.30286;-2.99389;,
 -0.50291;1.05540;-3.45929;,
 -0.63603;-0.09666;-3.65206;,
 -1.08252;-0.95010;-2.83460;,
 -1.15457;-0.09666;-2.93893;,
 -0.90864;-1.09155;-2.58273;,
 -0.73475;-0.95010;-2.33086;,
 -0.66270;-0.09666;-2.22653;,
 -0.73475;0.78137;-2.33086;,
 -0.90864;0.91523;-2.58273;,
 -1.08252;0.78137;-2.83460;,
 -1.15457;-0.09666;-2.93893;,
 -1.16392;-0.09666;-2.43836;,
 -1.16392;-0.09666;-2.43836;,
 -1.16392;-0.09666;-2.43836;,
 -1.16392;-0.09666;-2.43836;,
 -1.16392;-0.09666;-2.43836;,
 -1.16392;-0.09666;-2.43836;,
 -1.16392;-0.09666;-2.43836;,
 -1.16392;-0.09666;-2.43836;,
 -1.33266;3.35605;-3.29159;,
 3.84248;3.35605;-3.29159;,
 3.84248;2.22510;-3.72826;,
 -1.53895;2.22510;-3.72826;,
 8.91320;3.35605;-3.29159;,
 9.11949;2.22510;-3.72826;,
 3.84248;1.39624;-4.24401;,
 -1.55318;1.39624;-4.24401;,
 9.20294;1.39624;-4.24401;,
 8.91320;3.35605;-3.29159;,
 8.91320;3.76296;-0.00332;,
 9.11949;2.63201;-0.00332;,
 9.11949;2.22510;-3.72826;,
 8.91320;3.35605;3.28495;,
 9.11949;2.22510;3.72161;,
 9.20294;1.80312;-0.00332;,
 9.20294;1.39624;-4.24401;,
 9.20294;1.39624;4.23737;,
 8.91320;3.35605;3.28495;,
 3.84248;3.35605;3.28495;,
 3.84248;2.22510;3.72161;,
 9.11949;2.22510;3.72161;,
 -1.33266;3.35605;3.28495;,
 -1.53895;2.22510;3.72161;,
 3.84248;1.39624;4.23737;,
 9.20294;1.39624;4.23737;,
 -1.55318;1.39624;4.23737;,
 -1.33266;3.35605;3.28495;,
 -1.33266;3.76296;-0.00332;,
 -1.53895;2.63201;-0.00332;,
 -1.53895;2.22510;3.72161;,
 -1.33266;3.35605;-3.29159;,
 -1.53895;2.22510;-3.72826;,
 -1.55318;1.80312;-0.00332;,
 -1.55318;1.39624;4.23737;,
 -1.55318;1.39624;-4.24401;,
 3.84248;3.76296;-0.00332;,
 -1.33266;3.76296;-0.00332;,
 8.91320;3.76296;-0.00332;,
 3.84248;3.35605;-3.29159;,
 -1.33266;3.35605;-3.29159;,
 8.91320;3.35605;-3.29159;,
 -1.55318;1.80312;-0.00332;,
 3.84248;1.80312;-0.00332;,
 9.20294;1.80312;-0.00332;,
 -1.55318;1.39624;-4.24401;,
 3.84248;1.39624;-4.24401;,
 9.20294;1.39624;-4.24401;;
 
 152;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;79,80,81;,
 3;82,83,80;,
 3;84,85,83;,
 3;86,87,85;,
 3;88,89,87;,
 3;90,91,89;,
 3;92,93,91;,
 3;94,95,93;,
 4;81,80,96,97;,
 4;80,83,98,96;,
 4;83,85,99,98;,
 4;85,87,100,99;,
 4;87,89,101,100;,
 4;89,91,102,101;,
 4;91,93,103,102;,
 4;93,95,104,103;,
 4;97,96,105,106;,
 4;96,98,107,105;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;100,101,110,109;,
 4;101,102,111,110;,
 4;102,103,112,111;,
 4;103,104,113,112;,
 4;106,105,114,115;,
 4;105,107,116,114;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 4;110,111,120,119;,
 4;111,112,121,120;,
 4;112,113,122,121;,
 4;115,114,123,124;,
 4;114,116,125,123;,
 4;116,117,126,125;,
 4;117,118,127,126;,
 4;118,119,128,127;,
 4;119,120,129,128;,
 4;120,121,130,129;,
 4;121,122,131,130;,
 4;124,123,132,133;,
 4;123,125,134,132;,
 4;125,126,135,134;,
 4;126,127,136,135;,
 4;127,128,137,136;,
 4;128,129,138,137;,
 4;129,130,139,138;,
 4;130,131,140,139;,
 4;133,132,141,142;,
 4;132,134,143,141;,
 4;134,135,144,143;,
 4;135,136,145,144;,
 4;136,137,146,145;,
 4;137,138,147,146;,
 4;138,139,148,147;,
 4;139,140,149,148;,
 3;142,141,150;,
 3;141,143,151;,
 3;143,144,152;,
 3;144,145,153;,
 3;145,146,154;,
 3;146,147,155;,
 3;147,148,156;,
 3;148,149,157;,
 4;158,159,160,161;,
 4;159,162,163,160;,
 4;161,160,164,165;,
 4;160,163,166,164;,
 4;167,168,169,170;,
 4;168,171,172,169;,
 4;170,169,173,174;,
 4;169,172,175,173;,
 4;176,177,178,179;,
 4;177,180,181,178;,
 4;179,178,182,183;,
 4;178,181,184,182;,
 4;185,186,187,188;,
 4;186,189,190,187;,
 4;188,187,191,192;,
 4;187,190,193,191;,
 4;185,177,194,195;,
 4;177,171,196,194;,
 4;195,194,197,198;,
 4;194,196,199,197;,
 4;200,201,182,192;,
 4;201,202,175,182;,
 4;203,204,201,200;,
 4;204,205,202,201;;
 
 MeshMaterialList {
  7;
  152;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  4,
  4,
  5,
  5,
  4,
  4,
  5,
  5,
  4,
  4,
  5,
  5,
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
  162;
  0.999999;0.000003;0.001424;,
  0.727966;-0.685612;0.001065;,
  0.805767;-0.488945;0.334173;,
  0.838024;0.000001;0.545634;,
  0.805767;0.488946;0.334172;,
  0.727968;0.685610;0.001065;,
  0.805128;0.486916;-0.338648;,
  0.831838;0.000001;-0.555019;,
  0.805127;-0.486915;-0.338650;,
  0.389034;-0.921223;0.000701;,
  0.438140;-0.707778;0.554152;,
  0.446619;-0.000001;0.894724;,
  0.438147;0.707775;0.554149;,
  0.389045;0.921219;0.000701;,
  0.431449;0.704080;-0.564024;,
  0.427884;-0.000001;-0.903834;,
  0.431441;-0.704082;-0.564027;,
  0.170292;-0.985394;0.000023;,
  0.193431;-0.762817;0.617004;,
  0.199106;-0.000003;0.979978;,
  0.193430;0.762818;0.617004;,
  0.170291;0.985394;0.000024;,
  0.189673;0.756816;-0.625503;,
  0.189016;-0.000004;-0.981974;,
  0.189671;-0.756815;-0.625504;,
  0.000000;-1.000000;-0.000249;,
  0.000000;-0.774773;0.632239;,
  0.000000;-0.000003;1.000000;,
  0.000000;0.774775;0.632237;,
  0.000000;1.000000;-0.000247;,
  0.000000;0.768070;-0.640366;,
  0.000000;-0.000004;-1.000000;,
  0.000000;-0.768068;-0.640368;,
  -0.170294;-0.985393;0.000023;,
  -0.193432;-0.762817;0.617004;,
  -0.199107;-0.000003;0.979978;,
  -0.193431;0.762818;0.617003;,
  -0.170292;0.985394;0.000024;,
  -0.189674;0.756816;-0.625503;,
  -0.189018;-0.000004;-0.981974;,
  -0.189673;-0.756815;-0.625504;,
  -0.389031;-0.921224;0.000701;,
  -0.438136;-0.707779;0.554153;,
  -0.446616;-0.000001;0.894726;,
  -0.438144;0.707776;0.554150;,
  -0.389042;0.921220;0.000701;,
  -0.431446;0.704081;-0.564025;,
  -0.427881;-0.000001;-0.903835;,
  -0.431438;-0.704083;-0.564028;,
  -0.742260;-0.670111;0.001031;,
  -0.815169;-0.477482;0.327888;,
  -0.844205;0.000001;0.536021;,
  -0.815170;0.477482;0.327886;,
  -0.742262;0.670109;0.001031;,
  -0.814462;0.475533;-0.332446;,
  -0.838012;0.000001;-0.545651;,
  -0.814461;-0.475533;-0.332448;,
  -0.999999;0.000002;0.001294;,
  0.995958;-0.001658;-0.089802;,
  0.806981;-0.000924;-0.590577;,
  0.837170;-0.332923;-0.433946;,
  0.779829;-0.624628;0.041307;,
  0.543167;-0.431471;0.720279;,
  0.309244;-0.001547;0.950982;,
  0.544363;0.434445;0.717584;,
  0.877260;0.469875;-0.098142;,
  0.836707;0.337613;-0.431206;,
  0.411134;-0.000702;-0.911575;,
  0.426736;-0.538382;-0.726664;,
  0.315364;-0.948932;-0.008531;,
  0.124954;-0.607172;0.784684;,
  0.028107;-0.000839;0.999605;,
  0.120186;0.615183;0.779170;,
  0.300632;0.953691;-0.009677;,
  0.421201;0.548681;-0.722176;,
  -0.129410;-0.000046;-0.991591;,
  -0.046568;-0.615453;-0.786797;,
  0.130816;-0.990464;-0.043215;,
  0.277789;-0.636720;0.719319;,
  0.310794;-0.000031;0.950477;,
  0.273845;0.644822;0.713592;,
  0.124133;0.991384;-0.041823;,
  -0.047610;0.624389;-0.779661;,
  -0.492570;0.000243;-0.870273;,
  -0.382426;-0.630239;-0.675684;,
  0.002614;-0.999996;0.000959;,
  0.392886;-0.625671;0.673926;,
  0.505556;0.000251;0.862794;,
  0.389543;0.633944;0.668110;,
  0.002499;0.999996;0.000942;,
  -0.379123;0.638402;-0.669858;,
  -0.593056;-0.000044;-0.805161;,
  -0.496871;-0.626155;-0.600874;,
  -0.116687;-0.990105;0.077950;,
  0.265649;-0.616601;0.741103;,
  0.387423;-0.000030;0.921902;,
  0.264841;0.625025;0.734304;,
  -0.110529;0.991111;0.074043;,
  -0.491422;0.634232;-0.596871;,
  -0.722769;-0.000810;-0.691090;,
  -0.648320;-0.592890;-0.477663;,
  -0.274938;-0.943643;0.184248;,
  0.099172;-0.572789;0.813681;,
  0.235211;-0.000748;0.971944;,
  0.101413;0.582007;0.806835;,
  -0.261842;0.948949;0.175881;,
  -0.641065;0.601498;-0.476692;,
  -0.944225;-0.001308;-0.329299;,
  -0.914023;-0.396866;-0.084021;,
  -0.639990;-0.631930;0.437124;,
  -0.311662;-0.374276;0.873375;,
  -0.130768;-0.001188;0.991412;,
  -0.313367;0.378194;0.871074;,
  -0.635024;0.638904;0.434219;,
  -0.912681;0.400491;-0.081366;,
  -0.830647;-0.001782;0.556797;,
  0.566763;-0.001608;0.823879;,
  0.251186;0.879609;0.403972;,
  0.000000;0.360193;-0.932878;,
  0.000000;0.360192;-0.932878;,
  0.000000;0.446226;-0.894920;,
  0.000000;0.446226;-0.894920;,
  0.000000;0.528313;-0.849050;,
  0.983064;0.183261;0.000000;,
  0.000000;0.446226;-0.894921;,
  0.989664;0.143403;0.000000;,
  0.994648;0.103317;0.000000;,
  0.982841;0.183219;0.021316;,
  0.000000;0.360185;0.932881;,
  0.989538;0.143384;0.015960;,
  0.000000;0.446226;0.894920;,
  0.994593;0.103312;0.010578;,
  0.000000;0.528320;0.849045;,
  -0.983064;0.183260;0.000000;,
  0.000000;0.446226;0.894920;,
  -0.994904;0.100825;0.000000;,
  0.000000;0.528320;0.849045;,
  -0.999843;0.017710;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.982841;0.183219;-0.021316;,
  0.989538;0.143384;-0.015960;,
  0.994593;0.103312;-0.010578;,
  -0.982841;0.183219;0.021316;,
  -0.994837;0.100819;0.011605;,
  -0.982841;0.183219;-0.021316;,
  -0.994837;0.100819;-0.011605;,
  -0.999842;0.017710;0.001813;,
  -0.999842;0.017710;-0.001813;,
  0.000000;0.992430;0.122809;,
  0.000000;0.992430;0.122809;,
  0.000000;1.000000;0.000000;,
  0.000000;0.992430;0.122809;,
  0.000000;1.000000;0.000000;,
  0.000000;0.992430;-0.122809;,
  0.000000;0.992430;-0.122809;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.995429;-0.095508;,
  0.000000;-0.995429;-0.095508;,
  0.000000;-0.995429;0.095508;,
  0.000000;-0.995429;0.095508;,
  0.000000;-0.995429;0.095508;;
  152;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;58,60,59;,
  3;58,61,60;,
  3;58,62,61;,
  3;116,63,62;,
  3;116,64,63;,
  3;58,65,64;,
  3;58,66,65;,
  3;58,59,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,117,73,72;,
  4;65,66,74,73;,
  4;66,59,67,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,67,75,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,75,83,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,83,91,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,91,99,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,106,114,113;,
  4;106,99,107,114;,
  3;107,108,115;,
  3;108,109,115;,
  3;109,110,115;,
  3;110,111,115;,
  3;111,112,115;,
  3;112,113,115;,
  3;113,114,115;,
  3;114,107,115;,
  4;118,119,121,120;,
  4;119,119,124,121;,
  4;120,121,122,122;,
  4;121,124,122,122;,
  4;140,123,125,141;,
  4;123,127,129,125;,
  4;141,125,126,142;,
  4;125,129,131,126;,
  4;128,128,130,134;,
  4;128,128,134,130;,
  4;134,130,132,132;,
  4;130,134,136,132;,
  4;143,133,135,144;,
  4;133,145,146,135;,
  4;144,135,137,147;,
  4;135,146,148,137;,
  4;149,150,138,151;,
  4;150,152,153,138;,
  4;151,138,154,155;,
  4;138,153,154,154;,
  4;156,139,157,157;,
  4;139,156,158,157;,
  4;159,160,139,156;,
  4;160,161,156,139;;
 }
 MeshTextureCoords {
  206;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
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
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
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
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
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
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
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
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
