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
 298;
 -6.47966;12.28154;12.45393;,
 6.47966;12.28154;12.45393;,
 0.94977;12.28154;-16.56416;,
 -0.94977;12.28154;-16.56416;,
 -0.94977;0.25636;-16.56416;,
 0.94977;0.25636;-16.56416;,
 6.47966;0.25636;12.45393;,
 -6.47966;0.25636;12.45393;,
 -0.94977;7.49671;-16.56416;,
 0.94977;7.49671;-16.56416;,
 -6.47966;7.49671;12.45393;,
 6.47966;7.49671;12.45393;,
 0.94977;3.73438;-16.56416;,
 -0.94977;3.73438;-16.56416;,
 6.47966;3.73438;12.45393;,
 -6.47966;3.73438;12.45393;,
 -0.73680;3.73438;-16.30678;,
 0.73680;3.73438;-16.30678;,
 0.73680;7.49671;-16.30678;,
 -0.73680;7.49671;-16.30678;,
 6.26669;7.49671;12.27771;,
 6.26669;3.73438;12.27771;,
 -6.26669;3.73438;12.27771;,
 -6.26669;7.49671;12.27771;,
 4.07644;15.65946;10.52204;,
 3.83599;15.65946;10.47093;,
 3.87027;15.65946;10.65592;,
 3.94255;15.65946;10.31588;,
 4.12754;15.65946;10.28159;,
 4.28260;15.65946;10.38816;,
 4.31688;15.65946;10.57315;,
 4.21032;15.65946;10.72820;,
 4.02533;15.65946;10.76248;,
 4.07643;11.88697;10.52204;,
 4.07643;11.88697;9.20203;,
 5.00982;11.88697;9.58865;,
 5.39645;11.88697;10.52204;,
 5.00982;11.88697;11.45542;,
 4.07643;11.88697;11.84205;,
 3.14304;11.88697;11.45542;,
 2.75642;11.88697;10.52204;,
 3.14304;11.88697;9.58865;,
 5.58324;12.35287;9.01524;,
 6.20737;12.35287;10.52204;,
 4.07643;12.35287;8.39110;,
 5.58324;12.35287;12.02884;,
 2.56963;12.35287;9.01524;,
 4.07643;12.35287;12.65298;,
 1.94549;12.35287;10.52204;,
 2.56963;12.35287;12.02884;,
 6.60541;13.04374;10.52204;,
 5.86469;13.04374;8.73378;,
 5.86469;13.04374;12.31029;,
 4.07643;13.04374;7.99306;,
 4.07643;13.04374;13.05100;,
 2.28818;13.04374;8.73378;,
 2.28818;13.04374;12.31029;,
 1.54746;13.04374;10.52204;,
 6.24348;13.72988;9.98173;,
 5.99083;13.72988;11.67232;,
 5.22672;13.72988;8.60764;,
 4.61674;13.72988;12.68909;,
 3.53613;13.72988;8.35498;,
 2.92615;13.72988;12.43643;,
 2.16204;13.72988;9.37175;,
 1.90938;13.72988;11.06234;,
 5.53540;14.26166;11.41609;,
 4.47589;14.26166;12.18588;,
 5.74027;14.26166;10.12258;,
 3.18238;14.26166;11.98100;,
 4.97049;14.26166;9.06307;,
 2.41259;14.26166;10.92149;,
 3.67698;14.26166;8.85819;,
 2.61746;14.26166;9.62798;,
 3.96436;15.04380;11.50565;,
 3.30167;15.04380;11.13831;,
 4.69270;15.04380;11.29680;,
 3.09282;15.04380;10.40997;,
 5.06005;15.04380;10.63410;,
 3.46016;15.04380;9.74727;,
 4.85120;15.04380;9.90576;,
 4.18850;15.04380;9.53842;,
 0.03999;15.65946;10.52204;,
 -0.20046;15.65946;10.47093;,
 -0.16618;15.65946;10.65592;,
 -0.09390;15.65946;10.31588;,
 0.09109;15.65946;10.28159;,
 0.24615;15.65946;10.38816;,
 0.28043;15.65946;10.57315;,
 0.17387;15.65946;10.72820;,
 -0.01112;15.65946;10.76248;,
 0.03998;11.88697;10.52204;,
 0.03998;11.88697;9.20203;,
 0.97337;11.88697;9.58865;,
 1.36000;11.88697;10.52204;,
 0.97337;11.88697;11.45542;,
 0.03998;11.88697;11.84205;,
 -0.89341;11.88697;11.45542;,
 -1.28003;11.88697;10.52204;,
 -0.89341;11.88697;9.58865;,
 1.54679;12.35287;9.01524;,
 2.17092;12.35287;10.52204;,
 0.03998;12.35287;8.39110;,
 1.54679;12.35287;12.02884;,
 -1.46682;12.35287;9.01524;,
 0.03998;12.35287;12.65298;,
 -2.09096;12.35287;10.52204;,
 -1.46682;12.35287;12.02884;,
 2.56896;13.04374;10.52204;,
 1.82824;13.04374;8.73378;,
 1.82824;13.04374;12.31029;,
 0.03998;13.04374;7.99306;,
 0.03998;13.04374;13.05100;,
 -1.74827;13.04374;8.73378;,
 -1.74827;13.04374;12.31029;,
 -2.48899;13.04374;10.52204;,
 2.20703;13.72988;9.98173;,
 1.95438;13.72988;11.67232;,
 1.19027;13.72988;8.60764;,
 0.58029;13.72988;12.68909;,
 -0.50032;13.72988;8.35498;,
 -1.11030;13.72988;12.43643;,
 -1.87441;13.72988;9.37175;,
 -2.12707;13.72988;11.06234;,
 1.49895;14.26166;11.41609;,
 0.43944;14.26166;12.18588;,
 1.70382;14.26166;10.12258;,
 -0.85407;14.26166;11.98100;,
 0.93404;14.26166;9.06307;,
 -1.62386;14.26166;10.92149;,
 -0.35947;14.26166;8.85819;,
 -1.41899;14.26166;9.62798;,
 -0.07209;15.04380;11.50565;,
 -0.73478;15.04380;11.13831;,
 0.65625;15.04380;11.29680;,
 -0.94363;15.04380;10.40997;,
 1.02360;15.04380;10.63410;,
 -0.57629;15.04380;9.74727;,
 0.81475;15.04380;9.90576;,
 0.15205;15.04380;9.53842;,
 -4.16054;15.65946;10.52204;,
 -4.40098;15.65946;10.47093;,
 -4.36670;15.65946;10.65592;,
 -4.29442;15.65946;10.31588;,
 -4.10943;15.65946;10.28159;,
 -3.95438;15.65946;10.38816;,
 -3.92009;15.65946;10.57315;,
 -4.02665;15.65946;10.72820;,
 -4.21164;15.65946;10.76248;,
 -4.16054;11.88697;10.52204;,
 -4.16054;11.88697;9.20203;,
 -3.22715;11.88697;9.58865;,
 -2.84053;11.88697;10.52204;,
 -3.22715;11.88697;11.45542;,
 -4.16054;11.88697;11.84205;,
 -5.09393;11.88697;11.45542;,
 -5.48055;11.88697;10.52204;,
 -5.09393;11.88697;9.58865;,
 -2.65374;12.35287;9.01524;,
 -2.02960;12.35287;10.52204;,
 -4.16054;12.35287;8.39110;,
 -2.65374;12.35287;12.02884;,
 -5.66734;12.35287;9.01524;,
 -4.16054;12.35287;12.65298;,
 -6.29148;12.35287;10.52204;,
 -5.66734;12.35287;12.02884;,
 -1.63156;13.04374;10.52204;,
 -2.37228;13.04374;8.73378;,
 -2.37228;13.04374;12.31029;,
 -4.16054;13.04374;7.99306;,
 -4.16054;13.04374;13.05100;,
 -5.94879;13.04374;8.73378;,
 -5.94879;13.04374;12.31029;,
 -6.68951;13.04374;10.52204;,
 -1.99349;13.72988;9.98173;,
 -2.24615;13.72988;11.67232;,
 -3.01026;13.72988;8.60764;,
 -3.62023;13.72988;12.68909;,
 -4.70084;13.72988;8.35498;,
 -5.31082;13.72988;12.43643;,
 -6.07493;13.72988;9.37175;,
 -6.32759;13.72988;11.06234;,
 -2.70157;14.26166;11.41609;,
 -3.76108;14.26166;12.18588;,
 -2.49670;14.26166;10.12258;,
 -5.05459;14.26166;11.98100;,
 -3.26648;14.26166;9.06307;,
 -5.82438;14.26166;10.92149;,
 -4.55999;14.26166;8.85819;,
 -5.61951;14.26166;9.62798;,
 -4.27261;15.04380;11.50565;,
 -4.93530;15.04380;11.13831;,
 -3.54427;15.04380;11.29680;,
 -5.14415;15.04380;10.40997;,
 -3.17693;15.04380;10.63410;,
 -4.77681;15.04380;9.74727;,
 -3.38578;15.04380;9.90576;,
 -4.04847;15.04380;9.53842;,
 2.90195;18.68467;6.74188;,
 3.04793;18.55832;6.59591;,
 2.90195;18.55832;6.53544;,
 3.10840;18.55832;6.74188;,
 3.04793;18.55832;6.88786;,
 2.90195;18.55832;6.94833;,
 2.75597;18.55832;6.88786;,
 2.69551;18.55832;6.74188;,
 2.75597;18.55832;6.59591;,
 2.90195;12.43131;6.74188;,
 2.90195;12.43131;5.67134;,
 3.65894;12.43131;5.98489;,
 3.97249;12.43131;6.74188;,
 3.65894;12.43131;7.49887;,
 2.90195;12.43131;7.81243;,
 2.14496;12.43131;7.49887;,
 1.83141;12.43131;6.74188;,
 2.14496;12.43131;5.98489;,
 5.10355;12.91601;6.74188;,
 4.45872;12.91601;5.18512;,
 4.45872;12.91601;8.29865;,
 2.90195;12.91601;4.54029;,
 2.90195;12.91601;8.94348;,
 1.34519;12.91601;5.18512;,
 1.34519;12.91601;8.29865;,
 0.70036;12.91601;6.74188;,
 4.68060;13.73707;4.96324;,
 5.41734;13.73707;6.74188;,
 2.90195;13.73707;4.22650;,
 4.68060;13.73707;8.52053;,
 1.12331;13.73707;4.96324;,
 2.90195;13.73707;9.25727;,
 0.38657;13.73707;6.74188;,
 1.12331;13.73707;8.52053;,
 5.49101;14.82414;6.74188;,
 4.73270;14.82414;4.91114;,
 4.73270;14.82414;8.57263;,
 2.90195;14.82414;4.15282;,
 2.90195;14.82414;9.33095;,
 1.07121;14.82414;4.91114;,
 1.07121;14.82414;8.57263;,
 0.31289;14.82414;6.74188;,
 3.69578;17.23349;5.94805;,
 4.02459;17.23349;6.74188;,
 2.90195;17.23349;5.61924;,
 3.69578;17.23349;7.53571;,
 2.10812;17.23349;5.94805;,
 2.90195;17.23349;7.86453;,
 1.77931;17.23349;6.74188;,
 2.10812;17.23349;7.53571;,
 -2.37547;18.68467;6.74188;,
 -2.22950;18.55832;6.59591;,
 -2.37547;18.55832;6.53544;,
 -2.16903;18.55832;6.74188;,
 -2.22950;18.55832;6.88786;,
 -2.37547;18.55832;6.94833;,
 -2.52145;18.55832;6.88786;,
 -2.58192;18.55832;6.74188;,
 -2.52145;18.55832;6.59591;,
 -2.37547;12.43131;6.74188;,
 -2.37547;12.43131;5.67134;,
 -1.61848;12.43131;5.98489;,
 -1.30493;12.43131;6.74188;,
 -1.61848;12.43131;7.49887;,
 -2.37547;12.43131;7.81243;,
 -3.13246;12.43131;7.49887;,
 -3.44602;12.43131;6.74188;,
 -3.13246;12.43131;5.98489;,
 -0.17388;12.91601;6.74188;,
 -0.81871;12.91601;5.18512;,
 -0.81871;12.91601;8.29865;,
 -2.37547;12.91601;4.54029;,
 -2.37547;12.91601;8.94348;,
 -3.93224;12.91601;5.18512;,
 -3.93224;12.91601;8.29865;,
 -4.57707;12.91601;6.74188;,
 -0.59683;13.73707;4.96324;,
 0.13991;13.73707;6.74188;,
 -2.37547;13.73707;4.22650;,
 -0.59683;13.73707;8.52053;,
 -4.15412;13.73707;4.96324;,
 -2.37547;13.73707;9.25727;,
 -4.89086;13.73707;6.74188;,
 -4.15412;13.73707;8.52053;,
 0.21359;14.82414;6.74188;,
 -0.54473;14.82414;4.91114;,
 -0.54473;14.82414;8.57263;,
 -2.37547;14.82414;4.15282;,
 -2.37547;14.82414;9.33095;,
 -4.20622;14.82414;4.91114;,
 -4.20622;14.82414;8.57263;,
 -4.96454;14.82414;6.74188;,
 -1.58164;17.23349;5.94805;,
 -1.25283;17.23349;6.74188;,
 -2.37547;17.23349;5.61924;,
 -1.58164;17.23349;7.53571;,
 -3.16930;17.23349;5.94805;,
 -2.37547;17.23349;7.86453;,
 -3.49812;17.23349;6.74188;,
 -3.16930;17.23349;7.53571;;
 
 326;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,3,2,9;,
 4;8,10,0,3;,
 4;9,2,1,11;,
 4;10,11,1,0;,
 4;12,5,4,13;,
 4;12,14,6,5;,
 4;13,4,7,15;,
 4;14,15,7,6;,
 4;16,17,12,13;,
 4;18,19,8,9;,
 4;17,16,19,18;,
 4;20,18,9,11;,
 4;17,21,14,12;,
 4;17,18,20,21;,
 4;22,16,13,15;,
 4;19,23,10,8;,
 4;16,22,23,19;,
 4;23,20,11,10;,
 4;21,22,15,14;,
 4;21,20,23,22;,
 3;24,25,26;,
 3;24,27,25;,
 3;24,28,27;,
 3;24,29,28;,
 3;24,30,29;,
 3;24,31,30;,
 3;24,32,31;,
 3;24,26,32;,
 3;33,34,35;,
 3;33,35,36;,
 3;33,36,37;,
 3;33,37,38;,
 3;33,38,39;,
 3;33,39,40;,
 3;33,40,41;,
 3;33,41,34;,
 4;42,43,36,35;,
 4;42,35,34,44;,
 4;43,45,37,36;,
 4;44,34,41,46;,
 4;45,47,38,37;,
 4;46,41,40,48;,
 4;47,49,39,38;,
 4;48,40,39,49;,
 4;50,43,42,51;,
 4;50,52,45,43;,
 4;51,42,44,53;,
 4;52,54,47,45;,
 4;53,44,46,55;,
 4;54,56,49,47;,
 4;55,46,48,57;,
 4;56,57,48,49;,
 4;58,59,50,51;,
 4;58,51,53,60;,
 4;59,61,52,50;,
 4;60,53,55,62;,
 4;61,63,54,52;,
 4;62,55,57,64;,
 4;63,65,56,54;,
 4;64,57,56,65;,
 4;66,67,59,58;,
 4;66,58,60,68;,
 4;67,69,61,59;,
 4;68,60,62,70;,
 4;69,71,63,61;,
 4;70,62,64,72;,
 4;71,73,65,63;,
 4;72,64,65,73;,
 4;74,25,27,75;,
 4;74,75,67,66;,
 4;74,66,68,76;,
 4;74,76,26,25;,
 4;75,27,28,77;,
 4;75,77,69,67;,
 4;76,68,70,78;,
 4;76,78,32,26;,
 4;77,28,29,79;,
 4;77,79,71,69;,
 4;78,70,72,80;,
 4;78,80,31,32;,
 4;79,29,30,81;,
 4;79,81,73,71;,
 4;80,72,73,81;,
 4;80,81,30,31;,
 3;82,83,84;,
 3;82,85,83;,
 3;82,86,85;,
 3;82,87,86;,
 3;82,88,87;,
 3;82,89,88;,
 3;82,90,89;,
 3;82,84,90;,
 3;91,92,93;,
 3;91,93,94;,
 3;91,94,95;,
 3;91,95,96;,
 3;91,96,97;,
 3;91,97,98;,
 3;91,98,99;,
 3;91,99,92;,
 4;100,101,94,93;,
 4;100,93,92,102;,
 4;101,103,95,94;,
 4;102,92,99,104;,
 4;103,105,96,95;,
 4;104,99,98,106;,
 4;105,107,97,96;,
 4;106,98,97,107;,
 4;108,101,100,109;,
 4;108,110,103,101;,
 4;109,100,102,111;,
 4;110,112,105,103;,
 4;111,102,104,113;,
 4;112,114,107,105;,
 4;113,104,106,115;,
 4;114,115,106,107;,
 4;116,117,108,109;,
 4;116,109,111,118;,
 4;117,119,110,108;,
 4;118,111,113,120;,
 4;119,121,112,110;,
 4;120,113,115,122;,
 4;121,123,114,112;,
 4;122,115,114,123;,
 4;124,125,117,116;,
 4;124,116,118,126;,
 4;125,127,119,117;,
 4;126,118,120,128;,
 4;127,129,121,119;,
 4;128,120,122,130;,
 4;129,131,123,121;,
 4;130,122,123,131;,
 4;132,83,85,133;,
 4;132,133,125,124;,
 4;132,124,126,134;,
 4;132,134,84,83;,
 4;133,85,86,135;,
 4;133,135,127,125;,
 4;134,126,128,136;,
 4;134,136,90,84;,
 4;135,86,87,137;,
 4;135,137,129,127;,
 4;136,128,130,138;,
 4;136,138,89,90;,
 4;137,87,88,139;,
 4;137,139,131,129;,
 4;138,130,131,139;,
 4;138,139,88,89;,
 3;140,141,142;,
 3;140,143,141;,
 3;140,144,143;,
 3;140,145,144;,
 3;140,146,145;,
 3;140,147,146;,
 3;140,148,147;,
 3;140,142,148;,
 3;149,150,151;,
 3;149,151,152;,
 3;149,152,153;,
 3;149,153,154;,
 3;149,154,155;,
 3;149,155,156;,
 3;149,156,157;,
 3;149,157,150;,
 4;158,159,152,151;,
 4;158,151,150,160;,
 4;159,161,153,152;,
 4;160,150,157,162;,
 4;161,163,154,153;,
 4;162,157,156,164;,
 4;163,165,155,154;,
 4;164,156,155,165;,
 4;166,159,158,167;,
 4;166,168,161,159;,
 4;167,158,160,169;,
 4;168,170,163,161;,
 4;169,160,162,171;,
 4;170,172,165,163;,
 4;171,162,164,173;,
 4;172,173,164,165;,
 4;174,175,166,167;,
 4;174,167,169,176;,
 4;175,177,168,166;,
 4;176,169,171,178;,
 4;177,179,170,168;,
 4;178,171,173,180;,
 4;179,181,172,170;,
 4;180,173,172,181;,
 4;182,183,175,174;,
 4;182,174,176,184;,
 4;183,185,177,175;,
 4;184,176,178,186;,
 4;185,187,179,177;,
 4;186,178,180,188;,
 4;187,189,181,179;,
 4;188,180,181,189;,
 4;190,141,143,191;,
 4;190,191,183,182;,
 4;190,182,184,192;,
 4;190,192,142,141;,
 4;191,143,144,193;,
 4;191,193,185,183;,
 4;192,184,186,194;,
 4;192,194,148,142;,
 4;193,144,145,195;,
 4;193,195,187,185;,
 4;194,186,188,196;,
 4;194,196,147,148;,
 4;195,145,146,197;,
 4;195,197,189,187;,
 4;196,188,189,197;,
 4;196,197,146,147;,
 3;198,199,200;,
 3;198,201,199;,
 3;198,202,201;,
 3;198,203,202;,
 3;198,204,203;,
 3;198,205,204;,
 3;198,206,205;,
 3;198,200,206;,
 3;207,208,209;,
 3;207,209,210;,
 3;207,210,211;,
 3;207,211,212;,
 3;207,212,213;,
 3;207,213,214;,
 3;207,214,215;,
 3;207,215,208;,
 4;216,210,209,217;,
 4;216,218,211,210;,
 4;217,209,208,219;,
 4;218,220,212,211;,
 4;219,208,215,221;,
 4;220,222,213,212;,
 4;221,215,214,223;,
 4;222,223,214,213;,
 4;224,225,216,217;,
 4;224,217,219,226;,
 4;225,227,218,216;,
 4;226,219,221,228;,
 4;227,229,220,218;,
 4;228,221,223,230;,
 4;229,231,222,220;,
 4;230,223,222,231;,
 4;232,225,224,233;,
 4;232,234,227,225;,
 4;233,224,226,235;,
 4;234,236,229,227;,
 4;235,226,228,237;,
 4;236,238,231,229;,
 4;237,228,230,239;,
 4;238,239,230,231;,
 4;240,199,201,241;,
 4;240,241,232,233;,
 4;240,233,235,242;,
 4;240,242,200,199;,
 4;241,201,202,243;,
 4;241,243,234,232;,
 4;242,235,237,244;,
 4;242,244,206,200;,
 4;243,202,203,245;,
 4;243,245,236,234;,
 4;244,237,239,246;,
 4;244,246,205,206;,
 4;245,203,204,247;,
 4;245,247,238,236;,
 4;246,239,238,247;,
 4;246,247,204,205;,
 3;248,249,250;,
 3;248,251,249;,
 3;248,252,251;,
 3;248,253,252;,
 3;248,254,253;,
 3;248,255,254;,
 3;248,256,255;,
 3;248,250,256;,
 3;257,258,259;,
 3;257,259,260;,
 3;257,260,261;,
 3;257,261,262;,
 3;257,262,263;,
 3;257,263,264;,
 3;257,264,265;,
 3;257,265,258;,
 4;266,260,259,267;,
 4;266,268,261,260;,
 4;267,259,258,269;,
 4;268,270,262,261;,
 4;269,258,265,271;,
 4;270,272,263,262;,
 4;271,265,264,273;,
 4;272,273,264,263;,
 4;274,275,266,267;,
 4;274,267,269,276;,
 4;275,277,268,266;,
 4;276,269,271,278;,
 4;277,279,270,268;,
 4;278,271,273,280;,
 4;279,281,272,270;,
 4;280,273,272,281;,
 4;282,275,274,283;,
 4;282,284,277,275;,
 4;283,274,276,285;,
 4;284,286,279,277;,
 4;285,276,278,287;,
 4;286,288,281,279;,
 4;287,278,280,289;,
 4;288,289,280,281;,
 4;290,249,251,291;,
 4;290,291,282,283;,
 4;290,283,285,292;,
 4;290,292,250,249;,
 4;291,251,252,293;,
 4;291,293,284,282;,
 4;292,285,287,294;,
 4;292,294,256,250;,
 4;293,252,253,295;,
 4;293,295,286,284;,
 4;294,287,289,296;,
 4;294,296,255,256;,
 4;295,253,254,297;,
 4;295,297,288,286;,
 4;296,289,288,297;,
 4;296,297,254,255;;
 
 MeshMaterialList {
  3;
  326;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  2;;
  Material {
   0.800000;0.772000;0.693600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.759200;0.746400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.150400;0.210400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}