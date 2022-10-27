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
 344;
 0.00000;14.55120;-0.68058;,
 3.08089;14.55120;-1.68162;,
 0.00000;14.55120;-3.92002;,
 1.90409;14.55120;1.94018;,
 -1.90410;14.55120;1.94018;,
 -3.08089;14.55120;-1.68162;,
 2.50265;-0.55068;-1.55180;,
 3.08089;-0.51706;-1.68162;,
 1.90409;-0.51706;1.94018;,
 1.54672;-0.55068;1.39024;,
 0.00000;-0.55068;-3.37008;,
 0.00000;-0.51706;-3.92002;,
 -1.90410;-0.51706;1.94018;,
 -1.54672;-0.55068;1.39024;,
 -2.50265;-0.55068;-1.55180;,
 -3.08089;-0.51706;-1.68162;,
 -2.41642;0.45292;-1.53244;,
 -0.77775;0.49391;-1.16454;,
 -0.48068;0.49391;-0.25023;,
 -1.49343;0.45292;1.30823;,
 0.00000;0.45292;-3.28807;,
 0.00000;0.49391;-1.72960;,
 0.48068;0.49391;-0.25023;,
 1.49343;0.45292;1.30823;,
 2.41642;0.45292;-1.53244;,
 0.77775;0.49391;-1.16454;,
 0.77775;0.00882;-1.16454;,
 0.00000;0.00882;-1.72960;,
 0.00000;0.00882;-0.91183;,
 0.48068;0.00882;-0.25023;,
 -0.48068;0.00882;-0.25023;,
 -0.77775;0.00882;-1.16454;,
 0.00000;10.21834;-3.92002;,
 3.08089;10.21834;-1.68162;,
 -3.08089;10.21834;-1.68162;,
 1.90409;10.21834;1.94018;,
 -1.90410;10.21834;1.94018;,
 0.00000;10.90097;-3.92002;,
 3.08089;10.90097;-1.68162;,
 -3.08089;10.90097;-1.68162;,
 1.90409;10.90097;1.94018;,
 -1.90409;10.90097;1.94018;,
 2.54618;10.76901;-1.50788;,
 0.00000;10.76901;-3.35779;,
 0.00000;10.35030;-3.35779;,
 2.54618;10.35030;-1.50788;,
 -2.54618;10.35030;-1.50788;,
 -2.54618;10.76901;-1.50788;,
 1.57363;10.76901;1.48533;,
 1.57363;10.35030;1.48533;,
 -1.57363;10.35030;1.48533;,
 -1.57363;10.76901;1.48533;,
 0.00000;13.56431;-3.14354;,
 0.43097;13.49273;-3.33456;,
 0.00000;13.49273;-3.85428;,
 0.43097;13.49273;-2.95251;,
 0.00000;13.49273;-3.09019;,
 -0.43097;13.49273;-2.95251;,
 -0.43097;13.49273;-3.33456;,
 0.79633;13.28890;-3.49650;,
 0.00000;13.28890;-4.17817;,
 0.79633;13.28890;-2.79057;,
 0.00000;13.28890;-2.76630;,
 -0.79633;13.28890;-2.79057;,
 -0.79633;13.28890;-3.49650;,
 1.04046;12.98383;-3.60472;,
 0.00000;12.98383;-4.39458;,
 1.04046;12.98383;-2.68236;,
 0.00000;12.98383;-2.54989;,
 -1.04046;12.98383;-2.68236;,
 -1.04046;12.98383;-3.60472;,
 1.12619;12.62397;-3.64271;,
 0.00000;12.62397;-4.47057;,
 1.12619;12.62397;-2.64437;,
 0.00000;12.62397;-2.47389;,
 -1.12619;12.62397;-2.64437;,
 -1.12619;12.62397;-3.64271;,
 1.04046;12.26412;-3.60472;,
 0.00000;12.26412;-4.39458;,
 1.04046;12.26412;-2.68236;,
 0.00000;12.26412;-2.54989;,
 -1.04046;12.26412;-2.68236;,
 -1.04046;12.26412;-3.60472;,
 0.79633;11.95905;-3.49650;,
 0.00000;11.95905;-4.17817;,
 0.79633;11.95905;-2.79057;,
 0.00000;11.95905;-2.76630;,
 -0.79633;11.95905;-2.79057;,
 -0.79633;11.95905;-3.49650;,
 0.43097;11.75521;-3.33456;,
 0.00000;11.75521;-3.85428;,
 0.43097;11.75521;-2.95251;,
 0.00000;11.75521;-3.09019;,
 -0.43097;11.75521;-2.95251;,
 -0.43097;11.75521;-3.33456;,
 0.00000;11.68363;-3.14354;,
 3.16289;11.82959;1.12801;,
 3.16289;11.82959;-2.50474;,
 3.76966;14.08065;-2.50474;,
 3.76966;14.08065;1.12801;,
 -3.62141;11.82959;-2.50474;,
 -3.62141;11.82959;1.12801;,
 -4.14902;14.08065;1.12801;,
 -4.14902;14.08065;-2.50474;,
 -6.07284;16.80350;-2.50474;,
 -6.07284;16.56978;-2.50474;,
 -6.07284;16.56978;1.12801;,
 -6.07284;16.80350;1.12801;,
 6.07284;16.80350;-2.50474;,
 6.07284;16.80350;1.12801;,
 6.07284;16.56978;1.12801;,
 6.07284;16.56978;-2.50474;,
 -6.07284;19.79948;-2.50474;,
 -6.07284;19.79948;1.12801;,
 -6.07284;19.99237;1.12801;,
 -6.07284;19.99237;-2.50474;,
 6.07284;19.79948;-2.50474;,
 6.07284;19.99237;-2.50474;,
 6.07284;19.99237;1.12801;,
 6.07284;19.79948;1.12801;,
 -5.77069;20.36413;-2.50474;,
 -5.89089;16.63724;-2.50474;,
 -5.76295;20.60407;-2.50474;,
 -2.61823;26.81146;-2.50474;,
 -2.70450;26.09397;-2.50474;,
 -4.04448;14.95002;-2.50474;,
 -5.90027;16.34649;-2.50474;,
 -5.76295;20.60407;1.12801;,
 -2.61823;26.81146;1.12801;,
 -5.90027;16.34649;1.12801;,
 -5.77069;20.36413;1.12801;,
 -2.70450;26.09397;1.12801;,
 -4.04448;14.95002;1.12801;,
 -5.89089;16.63724;1.12801;,
 5.80188;20.25457;-2.50474;,
 5.89876;16.66950;-2.50474;,
 2.32515;26.09397;-2.50474;,
 2.23888;26.81146;-2.50474;,
 5.79565;20.48539;-2.50474;,
 5.90632;16.38981;-2.50474;,
 3.66513;14.95002;-2.50474;,
 2.23888;26.81146;1.12801;,
 5.79565;20.48539;1.12801;,
 5.90632;16.38981;1.12801;,
 2.32515;26.09397;1.12801;,
 5.80188;20.25457;1.12801;,
 5.89876;16.66950;1.12801;,
 3.66513;14.95002;1.12801;,
 -2.39589;26.81146;-2.50474;,
 -2.47426;26.09397;-2.50474;,
 -0.65277;39.31606;-2.50474;,
 -0.69944;39.31606;-2.50474;,
 -0.69944;39.31606;1.12801;,
 -0.65277;39.31606;1.12801;,
 -3.69156;14.95002;-2.50474;,
 -3.78653;14.08065;-2.50474;,
 -3.31084;11.82959;-2.50474;,
 -2.39589;26.81146;1.12801;,
 -2.47426;26.09397;1.12801;,
 -3.31084;11.82959;1.12801;,
 -3.78653;14.08065;1.12801;,
 -3.69156;14.95002;1.12801;,
 2.05610;26.81146;-2.50474;,
 2.13588;26.09397;-2.50474;,
 0.28172;39.31606;-2.50474;,
 0.28172;39.31606;1.12801;,
 0.32009;39.31606;1.12801;,
 0.32009;39.31606;-2.50474;,
 3.37500;14.95002;-2.50474;,
 3.47167;14.08065;-2.50474;,
 2.90758;11.82959;-2.50474;,
 2.05610;26.81146;1.12801;,
 2.13588;26.09397;1.12801;,
 2.90758;11.82959;1.12801;,
 3.47167;14.08065;1.12801;,
 3.37500;14.95002;1.12801;,
 -0.71727;38.85334;-2.50474;,
 0.34738;38.85334;-2.50474;,
 -0.77044;38.85334;-2.50474;,
 0.39109;38.85334;-2.50474;,
 -0.77044;38.85334;1.12801;,
 0.39109;38.85334;1.12801;,
 -0.71727;38.85334;1.12801;,
 0.34738;38.85334;1.12801;,
 -2.59856;26.12557;-2.08597;,
 -5.54481;20.61984;-2.08597;,
 -5.66031;17.03873;-2.08597;,
 -3.88613;15.41751;-2.08597;,
 5.66819;17.06973;-2.08597;,
 5.57510;20.51457;-2.08597;,
 3.52192;15.41751;-2.08597;,
 2.23436;26.12557;-2.08597;,
 -3.54701;15.41751;-2.08597;,
 -2.37733;26.12557;-2.08597;,
 2.05249;26.12557;-2.08597;,
 1.97583;26.81499;-2.08597;,
 -2.30202;26.81499;-2.08597;,
 3.24314;15.41751;-2.08597;,
 0.33394;38.38585;-2.08597;,
 -0.68906;38.38585;-2.08597;,
 -5.74570;16.89005;0.67271;,
 -5.62846;20.52514;0.67271;,
 -3.94477;15.24438;0.67271;,
 -2.63780;26.11387;0.67271;,
 2.26798;26.11387;0.67271;,
 5.65908;20.41829;0.67271;,
 5.75358;16.92151;0.67271;,
 3.57495;15.24438;0.67271;,
 -2.41322;26.11387;0.67271;,
 -3.60054;15.24438;0.67271;,
 -2.33678;26.81368;0.67271;,
 2.00555;26.81368;0.67271;,
 2.08337;26.11387;0.67271;,
 3.29197;15.24438;0.67271;,
 -0.69951;38.55898;0.67271;,
 0.33892;38.55898;0.67271;,
 18.44615;28.95082;0.29116;,
 19.11971;28.71890;-1.73923;,
 15.86822;25.04374;-1.73923;,
 15.55594;25.68403;0.29115;,
 21.07794;28.04462;-1.66928;,
 16.77612;23.18228;-1.66928;,
 20.95391;28.08734;0.74837;,
 16.71861;23.30018;0.74837;,
 10.97034;24.74418;-1.73923;,
 11.20226;25.41773;0.29115;,
 10.29607;22.78595;-1.66929;,
 10.33878;22.90999;0.74836;,
 7.29519;27.99568;-1.73923;,
 7.93546;28.30797;0.29115;,
 5.43372;27.08779;-1.66928;,
 5.55162;27.14529;0.74837;,
 6.99561;32.89355;-1.73923;,
 7.66918;32.66164;0.29115;,
 5.03739;33.56784;-1.66928;,
 5.16141;33.52512;0.74837;,
 10.24711;36.56870;-1.73924;,
 10.55940;35.92843;0.29115;,
 9.33923;38.43019;-1.66926;,
 9.39672;38.31226;0.74838;,
 15.14500;36.86826;-1.73922;,
 14.91308;36.19471;0.29113;,
 15.81927;38.82652;-1.66928;,
 15.77657;38.70247;0.74835;,
 18.82015;33.61677;-1.73923;,
 18.17988;33.30450;0.29115;,
 20.68161;34.52468;-1.66924;,
 20.56371;34.46716;0.74837;,
 2.33057;26.49890;-1.88779;,
 5.65928;20.60184;-1.88779;,
 5.65928;20.60184;0.56193;,
 2.33057;26.49890;0.56193;,
 7.10072;20.60184;-1.88779;,
 9.23516;22.44006;-1.88779;,
 9.23516;22.44006;0.56193;,
 7.10072;20.60184;0.56193;,
 5.89309;26.49890;-1.88779;,
 6.16223;26.49890;-1.75624;,
 6.16223;26.49890;0.56193;,
 5.89309;26.49890;0.56193;,
 4.37225;35.90165;-1.88779;,
 0.23307;39.32722;-1.88779;,
 0.23307;39.32722;0.56193;,
 4.37225;35.90165;0.56193;,
 4.64139;35.90165;0.56193;,
 4.64139;35.90165;-1.88779;,
 6.70816;26.00744;0.56193;,
 6.70816;26.00744;-1.74571;,
 10.11248;22.92047;0.56193;,
 10.11248;22.92047;-1.62317;,
 5.05698;33.33222;-1.75624;,
 5.05698;33.33222;0.56193;,
 4.78784;33.33222;-1.88779;,
 4.78784;33.33222;0.56193;,
 0.80624;35.82170;-1.88779;,
 0.80624;35.82170;0.56193;,
 5.99039;36.12290;-1.88779;,
 9.70700;38.79470;-1.73966;,
 5.99039;36.12290;0.56193;,
 9.70700;38.79470;0.56193;,
 -18.44615;28.95082;0.29116;,
 -15.55594;25.68403;0.29115;,
 -15.86822;25.04374;-1.73923;,
 -19.11971;28.71890;-1.73923;,
 -16.77612;23.18228;-1.66928;,
 -21.07794;28.04462;-1.66928;,
 -16.71861;23.30018;0.74837;,
 -20.95391;28.08734;0.74837;,
 -11.20226;25.41773;0.29115;,
 -10.97034;24.74418;-1.73923;,
 -10.29607;22.78595;-1.66929;,
 -10.33878;22.90999;0.74836;,
 -7.93546;28.30797;0.29115;,
 -7.29519;27.99568;-1.73923;,
 -5.43372;27.08779;-1.66928;,
 -5.55162;27.14529;0.74837;,
 -7.66918;32.66164;0.29115;,
 -6.99561;32.89355;-1.73923;,
 -5.03739;33.56784;-1.66928;,
 -5.16141;33.52512;0.74837;,
 -10.55940;35.92843;0.29115;,
 -10.24711;36.56870;-1.73924;,
 -9.33923;38.43019;-1.66926;,
 -9.39672;38.31226;0.74838;,
 -14.91308;36.19471;0.29113;,
 -15.14500;36.86826;-1.73922;,
 -15.81927;38.82652;-1.66928;,
 -15.77657;38.70247;0.74835;,
 -18.17988;33.30450;0.29115;,
 -18.82015;33.61677;-1.73923;,
 -20.68161;34.52468;-1.66924;,
 -20.56371;34.46716;0.74837;,
 -2.33057;26.49890;-1.88779;,
 -2.33057;26.49890;0.56193;,
 -5.65928;20.60184;0.56193;,
 -5.65928;20.60184;-1.88779;,
 -7.10072;20.60184;-1.88779;,
 -7.10072;20.60184;0.56193;,
 -9.23516;22.44006;0.56193;,
 -9.23516;22.44006;-1.88779;,
 -5.89309;26.49890;-1.88779;,
 -6.16223;26.49890;-1.75624;,
 -5.89309;26.49890;0.56193;,
 -6.16223;26.49890;0.56193;,
 -4.37225;35.90165;-1.88779;,
 -4.37225;35.90165;0.56193;,
 -0.23307;39.32722;0.56193;,
 -0.23307;39.32722;-1.88779;,
 -4.64139;35.90165;-1.88779;,
 -4.64139;35.90165;0.56193;,
 -6.70816;26.00744;0.56193;,
 -6.70816;26.00744;-1.74571;,
 -10.11248;22.92047;0.56193;,
 -10.11248;22.92047;-1.62317;,
 -5.05698;33.33222;-1.75624;,
 -5.05698;33.33222;0.56193;,
 -4.78784;33.33222;-1.88779;,
 -4.78784;33.33222;0.56193;,
 -0.80624;35.82170;-1.88779;,
 -0.80624;35.82170;0.56193;,
 -5.99039;36.12290;-1.88779;,
 -9.70700;38.79470;-1.73966;,
 -5.99039;36.12290;0.56193;,
 -9.70700;38.79470;0.56193;;
 
 345;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,2,5;,
 4;6,7,8,9;,
 4;6,10,11,7;,
 4;9,8,12,13;,
 4;10,14,15,11;,
 4;13,12,15,14;,
 4;16,17,18,19;,
 4;16,19,13,14;,
 4;16,14,10,20;,
 4;16,20,21,17;,
 4;19,18,22,23;,
 4;19,23,9,13;,
 4;20,10,6,24;,
 4;20,24,25,21;,
 4;23,22,25,24;,
 4;23,24,6,9;,
 4;26,27,21,25;,
 3;28,27,26;,
 4;29,26,25,22;,
 3;28,26,29;,
 4;30,29,22,18;,
 3;28,29,30;,
 4;31,30,18,17;,
 3;28,30,31;,
 4;27,31,17,21;,
 3;28,31,27;,
 4;32,33,7,11;,
 4;32,11,15,34;,
 4;33,35,8,7;,
 4;34,15,12,36;,
 4;35,36,12,8;,
 4;37,2,1,38;,
 4;37,39,5,2;,
 4;38,1,3,40;,
 4;39,41,4,5;,
 4;40,3,4,41;,
 4;42,43,37,38;,
 4;44,45,33,32;,
 4;43,42,45,44;,
 4;46,44,32,34;,
 4;43,47,39,37;,
 4;43,44,46,47;,
 4;48,42,38,40;,
 4;45,49,35,33;,
 4;42,48,49,45;,
 4;50,46,34,36;,
 4;47,51,41,39;,
 4;47,46,50,51;,
 4;51,48,40,41;,
 4;49,50,36,35;,
 4;48,51,50,49;,
 3;52,53,54;,
 3;52,55,53;,
 3;52,56,55;,
 3;52,57,56;,
 3;52,58,57;,
 3;52,54,58;,
 4;54,53,59,60;,
 4;53,55,61,59;,
 4;55,56,62,61;,
 4;56,57,63,62;,
 4;57,58,64,63;,
 4;58,54,60,64;,
 4;60,59,65,66;,
 4;59,61,67,65;,
 4;61,62,68,67;,
 4;62,63,69,68;,
 4;63,64,70,69;,
 4;64,60,66,70;,
 4;66,65,71,72;,
 4;65,67,73,71;,
 4;67,68,74,73;,
 4;68,69,75,74;,
 4;69,70,76,75;,
 4;70,66,72,76;,
 4;72,71,77,78;,
 4;71,73,79,77;,
 4;73,74,80,79;,
 4;74,75,81,80;,
 4;75,76,82,81;,
 4;76,72,78,82;,
 4;78,77,83,84;,
 4;77,79,85,83;,
 4;79,80,86,85;,
 4;80,81,87,86;,
 4;81,82,88,87;,
 4;82,78,84,88;,
 4;84,83,89,90;,
 4;83,85,91,89;,
 4;85,86,92,91;,
 4;86,87,93,92;,
 4;87,88,94,93;,
 4;88,84,90,94;,
 3;90,89,95;,
 3;89,91,95;,
 3;91,92,95;,
 3;92,93,95;,
 3;93,94,95;,
 3;94,90,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,104,107,113;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;116,119,109,108;,
 4;120,121,104,112;,
 4;120,112,115,122;,
 4;120,122,123,124;,
 4;121,125,103,126;,
 4;121,126,105,104;,
 4;122,115,114,127;,
 4;122,127,128,123;,
 4;126,103,102,129;,
 4;126,129,106,105;,
 4;127,114,113,130;,
 4;127,130,131,128;,
 4;129,102,132,133;,
 4;129,133,107,106;,
 4;130,113,107,133;,
 4;134,116,108,135;,
 4;134,136,137,138;,
 4;134,138,117,116;,
 4;135,108,111,139;,
 4;135,139,98,140;,
 4;138,137,141,142;,
 4;138,142,118,117;,
 4;139,111,110,143;,
 4;139,143,99,98;,
 4;142,141,144,145;,
 4;142,145,119,118;,
 4;143,110,109,146;,
 4;143,146,147,99;,
 4;145,146,109,119;,
 4;148,149,124,123;,
 4;150,151,152,153;,
 4;154,155,103,125;,
 4;155,156,100,103;,
 4;157,128,131,158;,
 4;156,159,101,100;,
 4;159,160,102,101;,
 4;161,132,102,160;,
 4;162,137,136,163;,
 4;164,150,153,165;,
 4;164,165,166,167;,
 4;168,140,98,169;,
 4;168,169,155,154;,
 4;169,98,97,170;,
 4;169,170,156,155;,
 4;171,172,144,141;,
 4;170,97,96,173;,
 4;170,173,159,156;,
 4;173,96,99,174;,
 4;173,174,160,159;,
 4;175,161,160,174;,
 4;175,174,99,147;,
 4;176,150,164,177;,
 4;176,148,123,178;,
 4;176,178,151,150;,
 4;177,164,167,179;,
 4;177,179,137,162;,
 4;178,123,128,180;,
 4;178,180,152,151;,
 4;179,167,166,181;,
 4;179,181,141,137;,
 4;180,128,157,182;,
 4;180,182,153,152;,
 4;181,166,165,183;,
 4;181,183,171,141;,
 4;182,183,165,153;,
 4;184,185,120,124;,
 4;186,187,125,121;,
 4;185,186,121,120;,
 4;185,184,187,186;,
 4;188,189,134,135;,
 4;190,188,135,140;,
 4;189,191,136,134;,
 4;189,188,190,191;,
 4;187,192,154,125;,
 4;193,184,124,149;,
 4;193,192,187,184;,
 4;194,195,162,163;,
 4;196,193,149,148;,
 4;195,194,193,196;,
 4;191,194,163,136;,
 4;197,190,140,168;,
 4;194,191,190,197;,
 4;192,197,168,154;,
 4;194,197,192,193;,
 4;198,199,176,177;,
 4;195,198,177,162;,
 4;199,196,148,176;,
 4;199,198,195,196;,
 4;200,201,130,133;,
 4;202,200,133,132;,
 4;201,203,131,130;,
 4;201,200,202,203;,
 4;204,205,145,144;,
 4;206,207,147,146;,
 4;205,206,146,145;,
 4;205,204,207,206;,
 4;203,208,158,131;,
 4;209,202,132,161;,
 4;208,203,202,209;,
 4;208,210,157,158;,
 4;211,212,172,171;,
 4;211,210,208,212;,
 4;213,209,161,175;,
 4;212,208,209,213;,
 4;207,213,175,147;,
 4;212,204,144,172;,
 4;212,213,207,204;,
 4;210,214,182,157;,
 4;215,211,171,183;,
 4;214,215,183,182;,
 4;214,210,211,215;,
 4;216,217,218,219;,
 4;217,220,221,218;,
 4;220,222,223,221;,
 4;222,216,219,223;,
 4;219,218,224,225;,
 4;218,221,226,224;,
 4;221,223,227,226;,
 4;223,219,225,227;,
 4;225,224,228,229;,
 4;224,226,230,228;,
 4;226,227,231,230;,
 4;227,225,229,231;,
 4;229,228,232,233;,
 4;228,230,234,232;,
 4;230,231,235,234;,
 4;231,229,233,235;,
 4;233,232,236,237;,
 4;232,234,238,236;,
 4;234,235,239,238;,
 4;235,233,237,239;,
 4;237,236,240,241;,
 4;236,238,242,240;,
 4;238,239,243,242;,
 4;239,237,241,243;,
 4;241,240,244,245;,
 4;240,242,246,244;,
 4;242,243,247,246;,
 4;243,241,245,247;,
 4;245,244,217,216;,
 4;244,246,220,217;,
 4;246,247,222,220;,
 4;247,245,216,222;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;252,255,250,249;,
 4;252,249,248,256;,
 4;252,256,257,253;,
 4;255,254,258,259;,
 4;255,259,251,250;,
 4;260,261,262,263;,
 4;260,263,264,265;,
 4;266,267,257,258;,
 4;268,266,258,254;,
 4;269,268,254,253;,
 4;267,269,253,257;,
 4;267,266,268,269;,
 4;270,271,258,257;,
 4;270,257,256,272;,
 4;270,272,260,265;,
 4;271,264,263,273;,
 4;271,273,259,258;,
 4;272,256,248,274;,
 4;272,274,261,260;,
 4;273,263,262,275;,
 4;273,275,251,259;,
 4;274,248,251,275;,
 4;274,275,262,261;,
 4;276,277,270,265;,
 4;278,276,265,264;,
 4;279,278,264,271;,
 4;277,279,271,270;,
 4;277,276,278,279;,
 4;280,281,282,283;,
 4;283,282,284,285;,
 4;285,284,286,287;,
 4;287,286,281,280;,
 4;281,288,289,282;,
 4;282,289,290,284;,
 4;284,290,291,286;,
 4;286,291,288,281;,
 4;288,292,293,289;,
 4;289,293,294,290;,
 4;290,294,295,291;,
 4;291,295,292,288;,
 4;292,296,297,293;,
 4;293,297,298,294;,
 4;294,298,299,295;,
 4;295,299,296,292;,
 4;296,300,301,297;,
 4;297,301,302,298;,
 4;298,302,303,299;,
 4;299,303,300,296;,
 4;300,304,305,301;,
 4;301,305,306,302;,
 4;302,306,307,303;,
 4;303,307,304,300;,
 4;304,308,309,305;,
 4;305,309,310,306;,
 4;306,310,311,307;,
 4;307,311,308,304;,
 4;308,280,283,309;,
 4;309,283,285,310;,
 4;310,285,287,311;,
 4;311,287,280,308;,
 4;312,313,314,315;,
 4;316,317,318,319;,
 4;316,315,314,317;,
 4;316,320,312,315;,
 4;316,319,321,320;,
 4;317,322,323,318;,
 4;317,314,313,322;,
 4;324,325,326,327;,
 4;324,328,329,325;,
 4;330,323,321,331;,
 4;332,318,323,330;,
 4;333,319,318,332;,
 4;331,321,319,333;,
 4;331,333,332,330;,
 4;334,321,323,335;,
 4;334,336,320,321;,
 4;334,328,324,336;,
 4;335,337,325,329;,
 4;335,323,322,337;,
 4;336,338,312,320;,
 4;336,324,327,338;,
 4;337,339,326,325;,
 4;337,322,313,339;,
 4;338,339,313,312;,
 4;338,327,326,339;,
 4;340,328,334,341;,
 4;342,329,328,340;,
 4;343,335,329,342;,
 4;341,334,335,343;,
 4;341,343,342,340;;
 
 MeshMaterialList {
  2;
  345;
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
  1;;
  Material {
   0.633600;0.633600;0.633600;1.000000;;
   5.000000;
   0.300000;0.300000;0.300000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.776000;0.745930;0.441350;1.000000;;
   17.000000;
   0.440000;0.440000;0.440000;;
   0.000000;0.000000;0.000000;;
  }
 }
}