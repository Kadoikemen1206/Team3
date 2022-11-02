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
 152;
 -0.20050;-0.22722;0.45605;,
 0.77902;-0.17564;-1.50532;,
 0.68163;-1.33433;-0.92912;,
 0.68163;-1.91629;0.46194;,
 0.68163;-1.33433;1.85301;,
 0.77902;-0.17564;2.42920;,
 0.77902;1.81303;1.85301;,
 0.77902;1.97512;0.46194;,
 0.77902;1.81303;-0.92912;,
 6.43703;2.71912;0.45330;,
 10.36554;2.19903;0.45330;,
 8.72429;1.28784;-1.91871;,
 6.43704;2.24254;-1.27913;,
 6.43704;2.24254;2.18572;,
 8.72429;1.28784;2.82531;,
 6.43703;-0.47946;-2.90123;,
 8.72429;-0.47945;-2.90123;,
 8.72428;-2.24683;-1.91871;,
 6.43703;-2.24681;-1.91871;,
 6.43703;-0.47946;3.80782;,
 6.43703;-2.24681;2.82531;,
 8.72428;-2.24683;2.82531;,
 8.72429;-0.47945;3.80782;,
 8.72428;-2.97888;0.45330;,
 6.43702;-2.97888;0.45330;,
 6.43703;1.28842;-2.99735;,
 8.72429;0.38416;-2.42111;,
 0.77902;1.40623;-1.43806;,
 6.43703;1.16917;3.75735;,
 8.72429;0.56671;3.22622;,
 0.77902;1.25259;2.47603;,
 13.78950;0.03438;0.45330;,
 13.78949;-0.90374;-0.81833;,
 13.78950;0.03437;-1.34505;,
 13.78949;-1.29224;0.45330;,
 13.78949;-0.90374;1.72492;,
 13.78950;0.03436;2.25164;,
 13.78950;1.36095;0.45330;,
 13.78950;0.97241;1.72492;,
 13.78950;0.97241;-0.81832;,
 13.78950;0.49276;-1.08766;,
 13.78950;0.58965;1.93985;,
 13.95205;0.64510;-1.66648;,
 13.95205;1.30528;-1.29598;,
 13.95205;0.01417;-2.02056;,
 14.01655;1.84711;0.45330;,
 13.95203;-1.27696;-1.29599;,
 13.95205;1.30528;2.20257;,
 13.95204;-1.81172;0.45330;,
 13.95205;0.77845;2.49824;,
 13.95203;-1.27696;2.20258;,
 13.95205;0.01417;2.92715;,
 2.79690;1.71987;-1.99800;,
 2.79690;-0.24505;-2.06945;,
 2.79691;2.26048;-1.28461;,
 2.66134;-1.71770;-1.32980;,
 2.79690;2.48268;0.45586;,
 2.66133;-2.44636;0.45586;,
 2.79691;2.26048;2.19633;,
 2.66134;-1.71770;2.24152;,
 2.79690;1.53273;3.03206;,
 2.79690;-0.24504;2.98116;,
 14.89343;2.15149;0.21992;,
 15.32950;1.99167;-0.34808;,
 14.89343;1.99167;-0.58335;,
 15.51011;1.99167;0.21992;,
 15.32950;1.99167;0.78792;,
 14.89343;1.99167;1.02319;,
 14.45737;1.99167;0.78792;,
 14.27673;1.99167;0.21992;,
 14.45737;1.99167;-0.34808;,
 15.69915;1.53672;-0.82960;,
 14.89343;1.53672;-1.26433;,
 16.03290;1.53672;0.21992;,
 15.69915;1.53672;1.26945;,
 14.89343;1.53672;1.70417;,
 14.08769;1.53672;1.26945;,
 13.75395;1.53672;0.21992;,
 14.08769;1.53672;-0.82960;,
 15.94616;0.85575;-1.15135;,
 14.89343;0.85575;-1.71934;,
 16.38223;0.85575;0.21992;,
 15.94616;0.85575;1.59119;,
 14.89343;0.85575;2.15919;,
 13.84068;0.85575;1.59119;,
 13.40462;0.85575;0.21992;,
 13.84068;0.85575;-1.15135;,
 14.89343;-0.75083;-1.71934;,
 15.94616;-0.75083;-1.15135;,
 15.69915;-1.43183;-0.82960;,
 14.89343;-1.43183;-1.26433;,
 16.38223;-0.75083;0.21992;,
 16.03290;-1.43183;0.21992;,
 15.94616;-0.75083;1.59119;,
 15.69915;-1.43183;1.26945;,
 14.89343;-0.75083;2.15919;,
 14.89343;-1.43183;1.70417;,
 13.84068;-0.75083;1.59119;,
 14.08769;-1.43183;1.26945;,
 13.40462;-0.75083;0.21992;,
 13.75395;-1.43183;0.21992;,
 13.84068;-0.75083;-1.15135;,
 14.08769;-1.43183;-0.82960;,
 15.32950;-1.88678;-0.34808;,
 14.89343;-1.88678;-0.58335;,
 15.51011;-1.88678;0.21992;,
 15.32950;-1.88678;0.78792;,
 14.89343;-1.88678;1.02319;,
 14.45737;-1.88678;0.78792;,
 14.27673;-1.88678;0.21992;,
 14.45737;-1.88678;-0.34808;,
 14.89343;-2.04660;0.21992;,
 14.89343;0.21300;-1.84719;,
 16.01556;0.21300;-1.24175;,
 13.77128;0.21300;-1.24175;,
 16.48038;0.21300;0.21992;,
 13.30647;0.21300;0.21992;,
 16.01556;0.21300;1.68159;,
 13.77128;0.21300;1.68159;,
 14.89343;0.21300;2.28704;,
 14.89343;-0.07117;-1.85453;,
 16.01955;-0.07117;-1.24694;,
 13.76730;-0.07117;-1.24694;,
 16.48601;-0.07117;0.21992;,
 13.30084;-0.07117;0.21992;,
 16.01955;-0.07117;1.68678;,
 13.76730;-0.07117;1.68678;,
 14.89343;-0.07117;2.29438;,
 15.86620;0.17948;-1.11822;,
 14.89343;0.17649;-1.66362;,
 15.88354;0.05246;-1.14080;,
 14.89343;0.05246;-1.69556;,
 13.92065;0.17948;-1.11822;,
 13.90331;0.05246;-1.14080;,
 16.28069;0.18249;0.21992;,
 16.30520;0.05246;0.21992;,
 13.50616;0.18249;0.21992;,
 13.48165;0.05246;0.21992;,
 15.86620;0.17948;1.55806;,
 15.88353;0.05246;1.58064;,
 13.92065;0.17948;1.55806;,
 13.90332;0.05246;1.58064;,
 14.89343;0.17649;2.10347;,
 14.89343;0.05246;2.13541;,
 14.89343;-0.03466;-1.67096;,
 15.87018;-0.03767;-1.12341;,
 13.91666;-0.03767;-1.12341;,
 16.28632;-0.04068;0.21992;,
 13.50053;-0.04068;0.21992;,
 15.87018;-0.03767;1.56325;,
 13.91666;-0.03767;1.56325;,
 14.89343;-0.03466;2.11081;;
 
 166;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,6,7;,
 3;0,7,8;,
 4;9,10,11,12;,
 4;9,13,14,10;,
 4;15,16,17,18;,
 4;19,20,21,22;,
 4;18,17,23,24;,
 4;20,24,23,21;,
 4;25,12,11,26;,
 4;25,26,16,15;,
 3;27,0,8;,
 3;27,1,0;,
 4;28,19,22,29;,
 4;28,29,14,13;,
 3;30,0,5;,
 3;30,6,0;,
 3;31,32,33;,
 3;31,34,32;,
 3;31,35,34;,
 3;31,36,35;,
 3;31,37,38;,
 3;31,39,37;,
 3;40,31,33;,
 3;40,39,31;,
 3;41,31,38;,
 3;41,36,31;,
 4;42,26,11,43;,
 4;42,43,39,40;,
 4;42,40,33,44;,
 4;42,44,16,26;,
 4;43,11,10,45;,
 4;43,45,37,39;,
 4;44,33,32,46;,
 4;44,46,17,16;,
 4;45,10,14,47;,
 4;45,47,38,37;,
 4;46,32,34,48;,
 4;46,48,23,17;,
 4;47,14,29,49;,
 4;47,49,41,38;,
 4;48,34,35,50;,
 4;48,50,21,23;,
 4;49,29,22,51;,
 4;49,51,36,41;,
 4;50,35,36,51;,
 4;50,51,22,21;,
 4;52,25,15,53;,
 4;52,53,1,27;,
 4;52,27,8,54;,
 4;52,54,12,25;,
 4;53,15,18,55;,
 4;53,55,2,1;,
 4;54,8,7,56;,
 4;54,56,9,12;,
 4;55,18,24,57;,
 4;55,57,3,2;,
 4;56,7,6,58;,
 4;56,58,13,9;,
 4;57,24,20,59;,
 4;57,59,4,3;,
 4;58,6,30,60;,
 4;58,60,28,13;,
 4;59,20,19,61;,
 4;59,61,5,4;,
 4;60,30,5,61;,
 4;60,61,19,28;,
 3;62,63,64;,
 3;62,65,63;,
 3;62,66,65;,
 3;62,67,66;,
 3;62,68,67;,
 3;62,69,68;,
 3;62,70,69;,
 3;62,64,70;,
 4;64,63,71,72;,
 4;63,65,73,71;,
 4;65,66,74,73;,
 4;66,67,75,74;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,64,72,78;,
 4;72,71,79,80;,
 4;71,73,81,79;,
 4;73,74,82,81;,
 4;74,75,83,82;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,72,80,86;,
 4;87,88,89,90;,
 4;88,91,92,89;,
 4;91,93,94,92;,
 4;93,95,96,94;,
 4;95,97,98,96;,
 4;97,99,100,98;,
 4;99,101,102,100;,
 4;101,87,90,102;,
 4;90,89,103,104;,
 4;89,92,105,103;,
 4;92,94,106,105;,
 4;94,96,107,106;,
 4;96,98,108,107;,
 4;98,100,109,108;,
 4;100,102,110,109;,
 4;102,90,104,110;,
 3;104,103,111;,
 3;103,105,111;,
 3;105,106,111;,
 3;106,107,111;,
 3;107,108,111;,
 3;108,109,111;,
 3;109,110,111;,
 3;110,104,111;,
 4;112,80,79,113;,
 4;112,114,86,80;,
 4;113,79,81,115;,
 4;114,116,85,86;,
 4;115,81,82,117;,
 4;116,118,84,85;,
 4;117,82,83,119;,
 4;118,119,83,84;,
 4;120,121,88,87;,
 4;120,87,101,122;,
 4;121,123,91,88;,
 4;122,101,99,124;,
 4;123,125,93,91;,
 4;124,99,97,126;,
 4;125,127,95,93;,
 4;126,97,95,127;,
 4;128,129,112,113;,
 4;129,128,130,131;,
 4;129,132,114,112;,
 4;129,131,133,132;,
 4;134,128,113,115;,
 4;128,134,135,130;,
 4;132,136,116,114;,
 4;132,133,137,136;,
 4;138,134,115,117;,
 4;134,138,139,135;,
 4;136,140,118,116;,
 4;136,137,141,140;,
 4;142,138,117,119;,
 4;138,142,143,139;,
 4;140,142,119,118;,
 4;140,141,143,142;,
 4;144,145,121,120;,
 4;144,131,130,145;,
 4;146,144,120,122;,
 4;144,146,133,131;,
 4;145,147,123,121;,
 4;145,130,135,147;,
 4;148,146,122,124;,
 4;146,148,137,133;,
 4;147,149,125,123;,
 4;147,135,139,149;,
 4;150,148,124,126;,
 4;148,150,141,137;,
 4;149,151,127,125;,
 4;149,139,143,151;,
 4;151,150,126,127;,
 4;150,151,143,141;;
 
 MeshMaterialList {
  11;
  166;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8;;
  Material {
   0.316800;0.160000;0.097600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "��.png";
   }
  }
  Material {
   0.097600;0.097600;0.097600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.920000;0.815120;0.743360;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.552000;0.486400;0.388800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.091200;0.351200;0.179200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.442400;0.373600;0.266400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.759200;0.420000;0.455200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.586400;0.307200;1.000000;;
   11.000000;
   0.310000;0.310000;0.310000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;0.460000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  178;
  0.113487;-0.070250;-0.991053;,
  0.107797;-0.772460;-0.625847;,
  0.109510;-0.993986;0.000000;,
  0.107797;-0.772459;0.625849;,
  0.114914;-0.059232;0.991608;,
  0.157243;0.783118;0.601665;,
  0.129998;0.991514;0.000000;,
  0.172508;0.788937;-0.589763;,
  -0.639341;-0.139724;-0.756121;,
  -0.643758;-0.545798;-0.536358;,
  -0.636036;-0.771660;-0.000062;,
  -0.643074;-0.546292;0.536676;,
  -0.635073;-0.167287;0.754120;,
  -0.672261;0.676582;0.300502;,
  -0.643440;0.765496;-0.000002;,
  -0.670071;0.687281;-0.280445;,
  -0.999800;0.019960;0.001465;,
  0.077174;0.997018;0.000001;,
  0.115792;0.879974;-0.460693;,
  0.101225;0.865250;0.491016;,
  -0.089668;-0.190746;-0.977535;,
  -0.079540;-0.178150;0.980783;,
  -0.098562;-0.762033;-0.639994;,
  -0.098130;-0.762059;0.640028;,
  -0.081056;-0.996709;0.000006;,
  0.048841;0.481352;-0.875166;,
  0.162270;0.479447;-0.862438;,
  -0.689644;0.321413;-0.648910;,
  0.042325;0.465218;0.884184;,
  0.147165;0.480410;0.864609;,
  -0.688482;0.277961;0.669873;,
  1.000000;-0.000004;-0.000000;,
  0.993096;-0.001039;0.117299;,
  0.990895;0.107705;0.080789;,
  0.988569;0.150766;-0.000002;,
  0.990894;0.107710;-0.080791;,
  0.993096;-0.001037;-0.117297;,
  0.987577;-0.131704;-0.085711;,
  0.980406;-0.196986;-0.000000;,
  0.987577;-0.131704;0.085710;,
  0.990661;-0.066745;0.118897;,
  0.990661;-0.066744;-0.118896;,
  0.101219;0.485151;-0.868552;,
  0.090000;0.758729;-0.645160;,
  0.972243;-0.002066;0.233965;,
  0.071501;0.997441;0.000001;,
  0.963525;0.214089;0.160582;,
  0.090031;0.758728;0.645156;,
  0.954347;0.298699;-0.000003;,
  0.101289;0.485147;0.868547;,
  0.963522;0.214099;-0.160585;,
  0.166347;0.003665;0.986061;,
  -0.225075;0.456033;-0.861032;,
  -0.252354;-0.214343;-0.943597;,
  -0.143976;0.915708;-0.375167;,
  -0.231976;-0.719917;-0.654146;,
  -0.136320;0.990665;0.000006;,
  -0.212170;-0.977233;0.000060;,
  -0.143685;0.901678;0.407836;,
  -0.229640;-0.720336;0.654509;,
  -0.210009;0.412064;0.886623;,
  -0.239442;-0.228744;0.943580;,
  0.962817;-0.132243;0.235574;,
  0.950087;-0.261489;0.170172;,
  0.166302;0.003670;-0.986068;,
  0.921992;-0.387209;-0.000000;,
  0.213994;-0.759274;-0.614581;,
  0.950086;-0.261490;-0.170174;,
  0.217444;-0.976073;0.000000;,
  0.962818;-0.132240;-0.235572;,
  0.213994;-0.759273;0.614582;,
  0.972244;-0.002062;-0.233961;,
  0.000001;1.000000;-0.000000;,
  -0.000000;0.925303;-0.379230;,
  0.334484;0.904954;-0.263019;,
  0.464190;0.885736;-0.000000;,
  0.334483;0.904955;0.263018;,
  -0.000000;0.925303;0.379229;,
  -0.334477;0.904956;0.263021;,
  -0.464182;0.885740;-0.000001;,
  -0.334480;0.904954;-0.263023;,
  0.000003;0.710544;-0.703653;,
  0.584649;0.660774;-0.470705;,
  0.786314;0.617827;-0.000001;,
  0.584648;0.660775;0.470705;,
  0.000003;0.710545;0.703652;,
  -0.584643;0.660779;0.470705;,
  -0.786311;0.617831;-0.000001;,
  -0.584645;0.660777;-0.470706;,
  0.000004;0.385598;-0.922667;,
  0.726071;0.342528;-0.596235;,
  0.951274;0.308348;-0.000000;,
  0.726072;0.342527;0.596234;,
  0.000004;0.385599;0.922667;,
  -0.726071;0.342528;0.596234;,
  -0.951274;0.308347;-0.000000;,
  -0.726070;0.342529;-0.596235;,
  0.000003;-0.385591;-0.922670;,
  0.726072;-0.342522;-0.596236;,
  0.951276;-0.308342;-0.000000;,
  0.726074;-0.342522;0.596235;,
  0.000003;-0.385592;0.922669;,
  -0.726074;-0.342519;0.596236;,
  -0.951277;-0.308337;-0.000000;,
  -0.726073;-0.342520;-0.596237;,
  0.000003;-0.710540;-0.703657;,
  0.584652;-0.660770;-0.470708;,
  0.786317;-0.617823;-0.000001;,
  0.584651;-0.660771;0.470707;,
  0.000002;-0.710541;0.703656;,
  -0.584646;-0.660775;0.470708;,
  -0.786314;-0.617827;-0.000001;,
  -0.584648;-0.660773;-0.470708;,
  -0.000000;-0.925303;-0.379230;,
  0.334484;-0.904954;-0.263019;,
  0.464190;-0.885736;-0.000000;,
  0.334483;-0.904955;0.263018;,
  -0.000000;-0.925303;0.379229;,
  -0.334477;-0.904956;0.263021;,
  -0.464182;-0.885740;-0.000001;,
  -0.334480;-0.904954;-0.263023;,
  0.000001;-1.000000;-0.000000;,
  0.000004;0.195085;-0.980786;,
  0.759336;0.170319;-0.628014;,
  -0.759335;0.170319;-0.628014;,
  0.988541;0.150952;0.000000;,
  -0.988541;0.150952;0.000000;,
  0.759338;0.170319;0.628011;,
  -0.759337;0.170319;0.628011;,
  0.000004;0.195085;0.980786;,
  0.000003;-0.195083;-0.980787;,
  0.759336;-0.170319;-0.628013;,
  -0.759337;-0.170313;-0.628014;,
  0.988541;-0.150952;-0.000000;,
  -0.988542;-0.150943;0.000000;,
  0.759338;-0.170319;0.628010;,
  -0.759339;-0.170313;0.628011;,
  0.000003;-0.195084;0.980787;,
  0.000003;-0.011029;-0.999939;,
  0.778386;-0.008985;-0.627722;,
  0.999973;-0.007393;0.000003;,
  0.778388;-0.008979;0.627719;,
  0.000002;-0.011032;0.999939;,
  -0.778388;-0.008957;0.627720;,
  -0.999973;-0.007364;0.000003;,
  -0.778385;-0.008956;-0.627723;,
  0.000001;-0.984337;-0.176298;,
  0.130631;-0.984968;-0.113024;,
  -0.130627;-0.984968;-0.113022;,
  0.162975;-0.986630;0.000000;,
  -0.162971;-0.986631;0.000000;,
  0.130631;-0.984968;0.113023;,
  -0.130628;-0.984968;0.113021;,
  0.000001;-0.984337;0.176297;,
  -0.000000;0.984341;-0.176274;,
  0.130587;0.984976;-0.113004;,
  -0.130590;0.984975;-0.113006;,
  0.162910;0.986641;-0.000000;,
  -0.162916;0.986640;-0.000000;,
  0.130588;0.984976;0.113003;,
  -0.130591;0.984975;0.113005;,
  -0.000000;0.984341;0.176273;,
  0.000005;0.247882;-0.968790;,
  0.760487;0.212818;-0.613489;,
  -0.760483;0.212831;-0.613489;,
  0.982421;0.186679;0.000003;,
  -0.982421;0.186679;0.000003;,
  0.760494;0.212786;0.613490;,
  -0.760493;0.212786;0.613492;,
  0.000002;0.247847;0.968799;,
  0.000001;-0.268844;-0.963184;,
  0.757604;-0.230236;-0.610760;,
  -0.757611;-0.230194;-0.610767;,
  0.979563;-0.201137;0.000003;,
  -0.979575;-0.201082;0.000003;,
  0.757614;-0.230192;0.610764;,
  -0.757621;-0.230151;0.610770;,
  0.000001;-0.268814;0.963192;;
  166;
  3;16,8,9;,
  3;16,9,10;,
  3;16,10,11;,
  3;16,11,12;,
  3;16,13,14;,
  3;16,14,15;,
  4;17,6,7,18;,
  4;17,19,5,6;,
  4;20,0,1,22;,
  4;21,23,3,4;,
  4;22,1,2,24;,
  4;23,24,2,3;,
  4;25,18,7,26;,
  4;25,26,0,20;,
  3;27,16,15;,
  3;27,8,16;,
  4;28,21,4,29;,
  4;28,29,5,19;,
  3;30,16,12;,
  3;30,13,16;,
  3;31,33,32;,
  3;31,34,33;,
  3;31,35,34;,
  3;31,36,35;,
  3;31,38,37;,
  3;31,39,38;,
  3;40,31,32;,
  3;40,39,31;,
  3;41,31,37;,
  3;41,36,31;,
  4;42,26,7,43;,
  4;62,63,39,40;,
  4;62,40,32,44;,
  4;42,64,0,26;,
  4;43,7,6,45;,
  4;63,65,38,39;,
  4;44,32,33,46;,
  4;64,66,1,0;,
  4;45,6,5,47;,
  4;65,67,37,38;,
  4;46,33,34,48;,
  4;66,68,2,1;,
  4;47,5,29,49;,
  4;67,69,41,37;,
  4;48,34,35,50;,
  4;68,70,3,2;,
  4;49,29,4,51;,
  4;69,71,36,41;,
  4;50,35,36,71;,
  4;70,51,4,3;,
  4;52,25,20,53;,
  4;52,53,8,27;,
  4;52,27,15,54;,
  4;52,54,18,25;,
  4;53,20,22,55;,
  4;53,55,9,8;,
  4;54,15,14,56;,
  4;54,56,17,18;,
  4;55,22,24,57;,
  4;55,57,10,9;,
  4;56,14,13,58;,
  4;56,58,19,17;,
  4;57,24,23,59;,
  4;57,59,11,10;,
  4;58,13,30,60;,
  4;58,60,28,19;,
  4;59,23,21,61;,
  4;59,61,12,11;,
  4;60,30,12,61;,
  4;60,61,21,28;,
  3;72,74,73;,
  3;72,75,74;,
  3;72,76,75;,
  3;72,77,76;,
  3;72,78,77;,
  3;72,79,78;,
  3;72,80,79;,
  3;72,73,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,73,81,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,81,89,96;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,97,105,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,105,113,120;,
  3;113,114,121;,
  3;114,115,121;,
  3;115,116,121;,
  3;116,117,121;,
  3;117,118,121;,
  3;118,119,121;,
  3;119,120,121;,
  3;120,113,121;,
  4;122,89,90,123;,
  4;122,124,96,89;,
  4;123,90,91,125;,
  4;124,126,95,96;,
  4;125,91,92,127;,
  4;126,128,94,95;,
  4;127,92,93,129;,
  4;128,129,93,94;,
  4;130,131,98,97;,
  4;130,97,104,132;,
  4;131,133,99,98;,
  4;132,104,103,134;,
  4;133,135,100,99;,
  4;134,103,102,136;,
  4;135,137,101,100;,
  4;136,102,101,137;,
  4;147,146,146,147;,
  4;162,163,139,138;,
  4;146,148,148,146;,
  4;162,138,145,164;,
  4;149,147,147,149;,
  4;163,165,140,139;,
  4;148,150,150,148;,
  4;164,145,144,166;,
  4;151,149,149,151;,
  4;165,167,141,140;,
  4;150,152,152,150;,
  4;166,144,143,168;,
  4;153,151,151,153;,
  4;167,169,142,141;,
  4;152,153,153,152;,
  4;168,143,142,169;,
  4;154,155,155,154;,
  4;170,138,139,171;,
  4;156,154,154,156;,
  4;170,172,145,138;,
  4;155,157,157,155;,
  4;171,139,140,173;,
  4;158,156,156,158;,
  4;172,174,144,145;,
  4;157,159,159,157;,
  4;173,140,141,175;,
  4;160,158,158,160;,
  4;174,176,143,144;,
  4;159,161,161,159;,
  4;175,141,142,177;,
  4;161,160,160,161;,
  4;176,177,142,143;;
 }
}