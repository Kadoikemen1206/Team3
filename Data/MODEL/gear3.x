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
 418;
 12.98048;-0.32280;-0.00000;,
 13.26464;1.45386;0.00000;,
 11.95103;1.45386;-5.75531;,
 11.69500;-0.32280;-5.63202;,
 17.27000;1.36200;0.00000;,
 17.10663;-0.35084;-0.00000;,
 15.41255;-0.35084;-7.42229;,
 15.55973;1.36200;-7.49317;,
 8.27037;1.45386;-10.37072;,
 8.09320;-0.32280;-10.14855;,
 10.66581;-0.35084;-13.37451;,
 10.76767;1.36200;-13.50223;,
 2.95166;1.45386;-12.93207;,
 2.88843;-0.32280;-12.65503;,
 3.80658;-0.35084;-16.67774;,
 3.84294;1.36200;-16.83701;,
 -2.95166;1.45386;-12.93207;,
 -2.88843;-0.32280;-12.65503;,
 -3.80659;-0.35084;-16.67774;,
 -3.84294;1.36200;-16.83700;,
 -8.27037;1.45386;-10.37072;,
 -8.09320;-0.32280;-10.14854;,
 -10.66582;-0.35084;-13.37451;,
 -10.76767;1.36200;-13.50223;,
 -11.95103;1.45386;-5.75531;,
 -11.69500;-0.32280;-5.63202;,
 -15.41255;-0.35084;-7.42229;,
 -15.55973;1.36200;-7.49317;,
 -13.26464;1.45386;0.00000;,
 -12.98048;-0.32280;0.00000;,
 -17.10663;-0.35084;0.00000;,
 -17.27000;1.36200;0.00000;,
 -11.95103;1.45386;5.75531;,
 -11.69500;-0.32280;5.63202;,
 -15.41255;-0.35084;7.42229;,
 -15.55973;1.36200;7.49317;,
 -8.27037;1.45386;10.37072;,
 -8.09320;-0.32280;10.14855;,
 -10.66581;-0.35084;13.37451;,
 -10.76767;1.36200;13.50223;,
 -2.95166;1.45386;12.93207;,
 -2.88842;-0.32280;12.65503;,
 -3.80658;-0.35084;16.67774;,
 -3.84293;1.36200;16.83701;,
 2.95166;1.45386;12.93207;,
 2.88844;-0.32280;12.65503;,
 3.80659;-0.35084;16.67774;,
 3.84295;1.36200;16.83700;,
 8.27038;1.45386;10.37071;,
 8.09320;-0.32280;10.14854;,
 10.66582;-0.35084;13.37450;,
 10.76768;1.36200;13.50222;,
 11.95103;1.45386;5.75530;,
 11.69501;-0.32280;5.63201;,
 15.41255;-0.35084;7.42228;,
 15.55974;1.36200;7.49316;,
 -12.91376;1.42935;-6.21894;,
 -8.93660;1.42935;-11.20614;,
 -14.33318;1.42935;0.00000;,
 -3.18944;1.42935;-13.97382;,
 -12.91376;1.42935;6.21894;,
 3.18943;1.42935;-13.97383;,
 -8.93660;1.42935;11.20614;,
 8.93660;1.42935;-11.20614;,
 -3.18943;1.42935;13.97383;,
 12.91376;1.42935;-6.21894;,
 3.18944;1.42935;13.97382;,
 14.33318;1.42935;0.00000;,
 8.93661;1.42935;11.20613;,
 12.91376;1.42935;6.21893;,
 -13.84552;1.40563;-6.66765;,
 -9.58140;1.40563;-12.01470;,
 -15.36737;1.40563;0.00000;,
 -3.41957;1.40563;-14.98208;,
 -13.84552;1.40563;6.66765;,
 3.41956;1.40563;-14.98208;,
 -9.58140;1.40563;12.01470;,
 9.58140;1.40563;-12.01470;,
 -3.41956;1.40563;14.98208;,
 13.84552;1.40563;-6.66765;,
 3.41957;1.40563;14.98208;,
 15.36737;1.40563;0.00000;,
 9.58141;1.40563;12.01469;,
 13.84553;1.40563;6.66764;,
 -8.91780;0.11465;-11.18257;,
 -12.88659;0.11465;-6.20585;,
 -13.81836;0.09093;-6.65457;,
 -9.56260;0.09093;-11.99112;,
 -15.33722;0.09093;0.00000;,
 -14.30303;0.11465;0.00000;,
 -3.18273;0.11465;-13.94443;,
 -3.41286;0.09093;-14.95268;,
 -13.81836;0.09093;6.65457;,
 -12.88659;0.11465;6.20585;,
 3.18272;0.11465;-13.94443;,
 3.41285;0.09093;-14.95269;,
 -9.56260;0.09093;11.99112;,
 -8.91780;0.11465;11.18257;,
 8.91780;0.11465;-11.18257;,
 9.56260;0.09093;-11.99112;,
 -3.41285;0.09093;14.95269;,
 -3.18272;0.11465;13.94443;,
 12.88659;0.11465;-6.20585;,
 13.81836;0.09093;-6.65457;,
 3.41286;0.09093;14.95268;,
 3.18273;0.11465;13.94443;,
 14.30303;0.11465;0.00000;,
 15.33722;0.09093;0.00000;,
 9.56261;0.09093;11.99111;,
 8.91781;0.11465;11.18256;,
 12.88660;0.11465;6.20585;,
 13.81836;0.09093;6.65456;,
 3.19840;-0.33226;-14.01313;,
 -3.19840;-0.33226;-14.01313;,
 8.96173;-0.33226;-11.23766;,
 -8.96173;-0.33226;-11.23765;,
 12.95007;-0.33226;-6.23643;,
 -12.95007;-0.33226;-6.23643;,
 14.37349;-0.33226;-0.00000;,
 -14.37349;-0.33226;0.00000;,
 12.95007;-0.33226;6.23642;,
 -12.95007;-0.33226;6.23643;,
 8.96174;-0.33226;11.23764;,
 -8.96173;-0.33226;11.23766;,
 3.19841;-0.33226;14.01313;,
 -3.19840;-0.33226;14.01313;,
 3.37223;-0.33757;-14.77472;,
 -3.37224;-0.33757;-14.77472;,
 9.44879;-0.33757;-11.84841;,
 -9.44879;-0.33757;-11.84841;,
 13.65389;-0.33757;-6.57537;,
 -13.65389;-0.33757;-6.57537;,
 15.15468;-0.33757;-0.00000;,
 -15.15468;-0.33757;0.00000;,
 13.65390;-0.33757;6.57536;,
 -13.65389;-0.33757;6.57537;,
 9.44880;-0.33757;11.84840;,
 -9.44879;-0.33757;11.84841;,
 3.37224;-0.33757;14.77472;,
 -3.37223;-0.33757;14.77472;,
 -3.19915;0.16087;-14.01639;,
 3.19915;0.16087;-14.01639;,
 3.37298;0.15557;-14.77799;,
 -3.37298;0.15557;-14.77799;,
 9.45088;0.15557;-11.85103;,
 8.96382;0.16087;-11.24028;,
 -8.96382;0.16087;-11.24027;,
 -9.45088;0.15557;-11.85103;,
 13.65691;0.15557;-6.57682;,
 12.95309;0.16087;-6.23788;,
 -12.95309;0.16087;-6.23788;,
 -13.65691;0.15557;-6.57682;,
 15.15803;0.15557;0.00000;,
 14.37684;0.16087;0.00000;,
 -14.37684;0.16087;0.00000;,
 -15.15803;0.15557;0.00000;,
 13.65692;0.15557;6.57681;,
 12.95309;0.16087;6.23787;,
 -12.95309;0.16087;6.23788;,
 -13.65691;0.15557;6.57682;,
 9.45089;0.15557;11.85102;,
 8.96383;0.16087;11.24026;,
 -8.96382;0.16087;11.24028;,
 -9.45088;0.15557;11.85103;,
 3.37299;0.15557;14.77799;,
 3.19916;0.16087;14.01639;,
 -3.19914;0.16087;14.01639;,
 -3.37297;0.15557;14.77799;,
 5.87336;0.21699;0.00000;,
 6.00194;0.87549;0.00000;,
 5.40756;0.87549;-2.60415;,
 5.29171;0.21699;-2.54836;,
 6.66154;0.85347;0.00000;,
 6.00184;0.85347;-2.89033;,
 6.59852;0.19277;0.00000;,
 5.94507;0.19277;-2.86299;,
 3.74215;0.87549;-4.69250;,
 3.66198;0.21699;-4.59198;,
 4.15340;0.85347;-5.20820;,
 4.11411;0.19277;-5.15893;,
 1.33555;0.87549;-5.85146;,
 1.30695;0.21699;-5.72611;,
 1.48233;0.85347;-6.49452;,
 1.46831;0.19277;-6.43308;,
 -1.33556;0.87549;-5.85146;,
 -1.30695;0.21699;-5.72611;,
 -1.48233;0.85347;-6.49452;,
 -1.46831;0.19277;-6.43308;,
 -3.74215;0.87549;-4.69250;,
 -3.66198;0.21699;-4.59198;,
 -4.15340;0.85347;-5.20820;,
 -4.11411;0.19277;-5.15893;,
 -5.40756;0.87549;-2.60415;,
 -5.29171;0.21699;-2.54836;,
 -6.00184;0.85347;-2.89033;,
 -5.94507;0.19277;-2.86299;,
 -6.00194;0.87549;0.00000;,
 -5.87336;0.21699;0.00000;,
 -6.66154;0.85347;0.00000;,
 -6.59852;0.19277;0.00000;,
 -5.40756;0.87549;2.60415;,
 -5.29171;0.21699;2.54836;,
 -6.00184;0.85347;2.89033;,
 -5.94507;0.19277;2.86299;,
 -3.74215;0.87549;4.69250;,
 -3.66198;0.21699;4.59198;,
 -4.15340;0.85347;5.20820;,
 -4.11411;0.19277;5.15893;,
 -1.33555;0.87549;5.85146;,
 -1.30694;0.21699;5.72611;,
 -1.48233;0.85347;6.49452;,
 -1.46831;0.19277;6.43308;,
 1.33556;0.87549;5.85146;,
 1.30695;0.21699;5.72611;,
 1.48234;0.85347;6.49452;,
 1.46831;0.19277;6.43308;,
 3.74215;0.87549;4.69250;,
 3.66199;0.21699;4.59197;,
 4.15341;0.85347;5.20819;,
 4.11411;0.19277;5.15893;,
 5.40756;0.87549;2.60414;,
 5.29172;0.21699;2.54835;,
 6.00184;0.85347;2.89033;,
 5.94507;0.19277;2.86299;,
 0.00000;0.01849;0.00000;,
 0.00000;0.01849;-5.15126;,
 3.64249;0.01849;-3.64249;,
 5.15126;0.01849;0.00000;,
 3.64249;0.01849;3.64249;,
 0.00000;0.01849;5.15126;,
 -3.64249;0.01849;3.64249;,
 -5.15126;0.01849;0.00000;,
 -3.64249;0.01849;-3.64249;,
 3.64249;0.67913;-3.64249;,
 1.96248;0.94475;-1.96248;,
 2.77537;0.94475;0.00000;,
 5.15126;0.67913;0.00000;,
 0.00000;0.67913;-5.15126;,
 0.00000;0.94475;-2.77537;,
 1.96248;0.94475;1.96248;,
 3.64249;0.67913;3.64249;,
 -3.64249;0.67913;-3.64249;,
 -1.96249;0.94475;-1.96248;,
 0.00000;0.94475;2.77537;,
 0.00000;0.67913;5.15126;,
 -5.15126;0.67913;0.00000;,
 -2.77537;0.94475;0.00000;,
 -1.96249;0.94475;1.96248;,
 -3.64249;0.67913;3.64249;,
 0.00000;1.46239;-2.77537;,
 1.96248;1.46239;-1.96248;,
 0.00000;1.46239;0.00000;,
 2.77537;1.46239;0.00000;,
 1.96248;1.46239;1.96248;,
 0.00000;1.46239;2.77537;,
 -1.96249;1.46239;1.96248;,
 -2.77537;1.46239;0.00000;,
 -1.96249;1.46239;-1.96248;,
 -16.30323;1.01138;-0.49911;,
 16.30323;1.01138;-0.49911;,
 16.30323;-0.06439;-0.49911;,
 -16.30323;-0.06439;-0.49911;,
 16.30323;1.01138;0.49911;,
 16.30323;-0.06439;0.49911;,
 -16.30323;1.01138;0.49911;,
 -16.30323;-0.06439;0.49911;,
 -0.49389;1.01138;16.30338;,
 -0.50433;1.01138;-16.30306;,
 -0.50433;-0.06439;-16.30306;,
 -0.49389;-0.06439;16.30338;,
 0.49389;1.01138;-16.30338;,
 0.49389;-0.06439;-16.30338;,
 0.50433;1.01138;16.30306;,
 0.50433;-0.06439;16.30306;,
 -11.88024;1.01138;11.17604;,
 11.17435;1.01138;-11.88185;,
 11.17435;-0.06439;-11.88185;,
 -11.88024;-0.06439;11.17604;,
 11.88024;1.01138;-11.17604;,
 11.88024;-0.06439;-11.17604;,
 -11.17435;1.01138;11.88185;,
 -11.17435;-0.06439;11.88185;,
 11.17985;1.01138;11.87666;,
 -11.88543;1.01138;-11.17054;,
 -11.88543;-0.06439;-11.17054;,
 11.17985;-0.06439;11.87666;,
 -11.17985;1.01138;-11.87666;,
 -11.17985;-0.06439;-11.87666;,
 11.88543;1.01138;11.17054;,
 11.88543;-0.06439;11.17054;,
 -7.48021;1.09876;19.42267;,
 -9.22766;1.11651;18.54125;,
 -9.23797;-0.03701;18.53847;,
 -7.49052;-0.05476;19.41988;,
 -6.84954;1.10662;13.82633;,
 -6.85985;-0.04689;13.82354;,
 -5.10209;1.08887;14.70775;,
 -5.11241;-0.06464;14.70496;,
 -14.11134;1.10169;15.40623;,
 -15.46176;1.12467;13.98967;,
 -15.47444;-0.02880;13.98303;,
 -14.12401;-0.05178;15.39958;,
 -11.63975;1.10365;10.34579;,
 -11.65241;-0.04983;10.33915;,
 -10.28934;1.08067;11.76235;,
 -10.30200;-0.07281;11.75572;,
 -19.34518;1.10728;9.11820;,
 -20.16243;1.13371;7.33994;,
 -20.17601;-0.01972;7.32904;,
 -19.35876;-0.04616;9.10729;,
 -15.36447;1.09802;5.13438;,
 -15.37805;-0.05542;5.12348;,
 -14.54723;1.07158;6.91264;,
 -14.56081;-0.08185;6.90174;,
 -21.63835;1.11666;1.26148;,
 -21.70568;1.14464;-0.69441;,
 -21.71848;-0.00874;-0.71048;,
 -21.65114;-0.03672;1.24541;,
 -16.42840;1.08858;-0.87685;,
 -16.44119;-0.06480;-0.89290;,
 -16.36107;1.06060;1.07904;,
 -16.37387;-0.09278;1.06298;,
 -0.97862;1.10271;20.20371;,
 -0.97862;-0.05085;20.20371;,
 0.97862;-0.05085;20.20371;,
 0.97862;1.10271;20.20371;,
 0.97862;-0.05085;14.92298;,
 0.97862;1.10271;14.92298;,
 -0.97862;-0.05085;14.92298;,
 -0.97862;1.10271;14.92298;,
 7.48021;1.09876;19.42267;,
 7.49052;-0.05476;19.41988;,
 9.23797;-0.03701;18.53847;,
 9.22766;1.11651;18.54125;,
 6.85985;-0.04689;13.82354;,
 6.84954;1.10662;13.82633;,
 5.11241;-0.06464;14.70496;,
 5.10209;1.08887;14.70775;,
 14.11134;1.10169;15.40623;,
 14.12401;-0.05178;15.39958;,
 15.47444;-0.02880;13.98303;,
 15.46176;1.12467;13.98967;,
 11.65241;-0.04983;10.33915;,
 11.63975;1.10365;10.34579;,
 10.30200;-0.07281;11.75572;,
 10.28934;1.08067;11.76235;,
 19.34518;1.10728;9.11820;,
 19.35876;-0.04616;9.10729;,
 20.17601;-0.01972;7.32904;,
 20.16243;1.13371;7.33994;,
 15.37805;-0.05542;5.12348;,
 15.36447;1.09802;5.13438;,
 14.56081;-0.08185;6.90174;,
 14.54723;1.07158;6.91264;,
 21.63835;1.11666;1.26148;,
 21.65114;-0.03672;1.24541;,
 21.71848;-0.00874;-0.71048;,
 21.70568;1.14464;-0.69441;,
 16.44119;-0.06480;-0.89290;,
 16.42840;1.08858;-0.87685;,
 16.37387;-0.09278;1.06298;,
 16.36107;1.06060;1.07904;,
 -7.48021;1.09876;-19.42267;,
 -7.49052;-0.05476;-19.41988;,
 -9.23797;-0.03701;-18.53847;,
 -9.22766;1.11651;-18.54125;,
 -6.85985;-0.04689;-13.82354;,
 -6.84954;1.10662;-13.82633;,
 -5.11241;-0.06464;-14.70496;,
 -5.10209;1.08887;-14.70775;,
 -14.11134;1.10169;-15.40623;,
 -14.12401;-0.05178;-15.39958;,
 -15.47444;-0.02880;-13.98303;,
 -15.46176;1.12467;-13.98967;,
 -11.65241;-0.04983;-10.33915;,
 -11.63975;1.10365;-10.34579;,
 -10.30200;-0.07281;-11.75572;,
 -10.28934;1.08067;-11.76235;,
 -19.34518;1.10728;-9.11820;,
 -19.35876;-0.04616;-9.10729;,
 -20.17601;-0.01972;-7.32904;,
 -20.16243;1.13371;-7.33994;,
 -15.37805;-0.05542;-5.12348;,
 -15.36447;1.09802;-5.13438;,
 -14.56081;-0.08185;-6.90174;,
 -14.54723;1.07158;-6.91264;,
 -0.97862;1.10271;-20.20371;,
 0.97862;1.10271;-20.20371;,
 0.97862;-0.05085;-20.20371;,
 -0.97862;-0.05085;-20.20371;,
 0.97862;1.10271;-14.92298;,
 0.97862;-0.05085;-14.92298;,
 -0.97862;1.10271;-14.92298;,
 -0.97862;-0.05085;-14.92298;,
 7.48021;1.09876;-19.42267;,
 9.22766;1.11651;-18.54125;,
 9.23797;-0.03701;-18.53847;,
 7.49052;-0.05476;-19.41988;,
 6.84954;1.10662;-13.82633;,
 6.85985;-0.04689;-13.82354;,
 5.10209;1.08887;-14.70775;,
 5.11241;-0.06464;-14.70496;,
 14.11134;1.10169;-15.40623;,
 15.46176;1.12467;-13.98967;,
 15.47444;-0.02880;-13.98303;,
 14.12401;-0.05178;-15.39958;,
 11.63975;1.10365;-10.34579;,
 11.65241;-0.04983;-10.33915;,
 10.28934;1.08067;-11.76235;,
 10.30200;-0.07281;-11.75572;,
 19.34518;1.10728;-9.11820;,
 20.16243;1.13371;-7.33994;,
 20.17601;-0.01972;-7.32904;,
 19.35876;-0.04616;-9.10729;,
 15.36447;1.09802;-5.13438;,
 15.37805;-0.05542;-5.12348;,
 14.54723;1.07158;-6.91264;,
 14.56081;-0.08185;-6.90174;;
 
 384;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,2,8,9;,
 4;7,6,10,11;,
 4;9,8,12,13;,
 4;11,10,14,15;,
 4;13,12,16,17;,
 4;15,14,18,19;,
 4;17,16,20,21;,
 4;19,18,22,23;,
 4;21,20,24,25;,
 4;23,22,26,27;,
 4;25,24,28,29;,
 4;27,26,30,31;,
 4;29,28,32,33;,
 4;31,30,34,35;,
 4;33,32,36,37;,
 4;35,34,38,39;,
 4;37,36,40,41;,
 4;39,38,42,43;,
 4;41,40,44,45;,
 4;43,42,46,47;,
 4;45,44,48,49;,
 4;47,46,50,51;,
 4;49,48,52,53;,
 4;51,50,54,55;,
 4;53,52,1,0;,
 4;55,54,5,4;,
 4;56,24,20,57;,
 4;56,58,28,24;,
 4;57,20,16,59;,
 4;58,60,32,28;,
 4;59,16,12,61;,
 4;60,62,36,32;,
 4;61,12,8,63;,
 4;62,64,40,36;,
 4;63,8,2,65;,
 4;64,66,44,40;,
 4;65,2,1,67;,
 4;66,68,48,44;,
 4;67,1,52,69;,
 4;68,69,52,48;,
 4;70,71,23,27;,
 4;70,27,31,72;,
 4;71,73,19,23;,
 4;72,31,35,74;,
 4;73,75,15,19;,
 4;74,35,39,76;,
 4;75,77,11,15;,
 4;76,39,43,78;,
 4;77,79,7,11;,
 4;78,43,47,80;,
 4;79,81,4,7;,
 4;80,47,51,82;,
 4;81,83,55,4;,
 4;82,51,55,83;,
 4;84,85,56,57;,
 4;86,87,71,70;,
 4;86,85,84,87;,
 4;88,86,70,72;,
 4;85,89,58,56;,
 4;86,88,89,85;,
 4;90,84,57,59;,
 4;87,91,73,71;,
 4;87,84,90,91;,
 4;92,88,72,74;,
 4;89,93,60,58;,
 4;88,92,93,89;,
 4;94,90,59,61;,
 4;91,95,75,73;,
 4;91,90,94,95;,
 4;96,92,74,76;,
 4;93,97,62,60;,
 4;92,96,97,93;,
 4;98,94,61,63;,
 4;95,99,77,75;,
 4;95,94,98,99;,
 4;100,96,76,78;,
 4;97,101,64,62;,
 4;96,100,101,97;,
 4;102,98,63,65;,
 4;99,103,79,77;,
 4;99,98,102,103;,
 4;104,100,78,80;,
 4;101,105,66,64;,
 4;100,104,105,101;,
 4;106,102,65,67;,
 4;103,107,81,79;,
 4;103,102,106,107;,
 4;108,104,80,82;,
 4;105,109,68,66;,
 4;104,108,109,105;,
 4;110,106,67,69;,
 4;107,111,83,81;,
 4;107,106,110,111;,
 4;111,108,82,83;,
 4;109,110,69,68;,
 4;108,111,110,109;,
 4;112,13,17,113;,
 4;112,114,9,13;,
 4;113,17,21,115;,
 4;114,116,3,9;,
 4;115,21,25,117;,
 4;116,118,0,3;,
 4;117,25,29,119;,
 4;118,120,53,0;,
 4;119,29,33,121;,
 4;120,122,49,53;,
 4;121,33,37,123;,
 4;122,124,45,49;,
 4;123,37,41,125;,
 4;124,125,41,45;,
 4;126,127,18,14;,
 4;126,14,10,128;,
 4;127,129,22,18;,
 4;128,10,6,130;,
 4;129,131,26,22;,
 4;130,6,5,132;,
 4;131,133,30,26;,
 4;132,5,54,134;,
 4;133,135,34,30;,
 4;134,54,50,136;,
 4;135,137,38,34;,
 4;136,50,46,138;,
 4;137,139,42,38;,
 4;138,46,42,139;,
 4;140,141,112,113;,
 4;142,143,127,126;,
 4;142,141,140,143;,
 4;144,142,126,128;,
 4;141,145,114,112;,
 4;142,144,145,141;,
 4;146,140,113,115;,
 4;143,147,129,127;,
 4;143,140,146,147;,
 4;148,144,128,130;,
 4;145,149,116,114;,
 4;144,148,149,145;,
 4;150,146,115,117;,
 4;147,151,131,129;,
 4;147,146,150,151;,
 4;152,148,130,132;,
 4;149,153,118,116;,
 4;148,152,153,149;,
 4;154,150,117,119;,
 4;151,155,133,131;,
 4;151,150,154,155;,
 4;156,152,132,134;,
 4;153,157,120,118;,
 4;152,156,157,153;,
 4;158,154,119,121;,
 4;155,159,135,133;,
 4;155,154,158,159;,
 4;160,156,134,136;,
 4;157,161,122,120;,
 4;156,160,161,157;,
 4;162,158,121,123;,
 4;159,163,137,135;,
 4;159,158,162,163;,
 4;164,160,136,138;,
 4;161,165,124,122;,
 4;160,164,165,161;,
 4;166,162,123,125;,
 4;163,167,139,137;,
 4;163,162,166,167;,
 4;167,164,138,139;,
 4;165,166,125,124;,
 4;164,167,166,165;,
 4;168,169,170,171;,
 4;169,172,173,170;,
 4;172,174,175,173;,
 4;174,168,171,175;,
 4;171,170,176,177;,
 4;170,173,178,176;,
 4;173,175,179,178;,
 4;175,171,177,179;,
 4;177,176,180,181;,
 4;176,178,182,180;,
 4;178,179,183,182;,
 4;179,177,181,183;,
 4;181,180,184,185;,
 4;180,182,186,184;,
 4;182,183,187,186;,
 4;183,181,185,187;,
 4;185,184,188,189;,
 4;184,186,190,188;,
 4;186,187,191,190;,
 4;187,185,189,191;,
 4;189,188,192,193;,
 4;188,190,194,192;,
 4;190,191,195,194;,
 4;191,189,193,195;,
 4;193,192,196,197;,
 4;192,194,198,196;,
 4;194,195,199,198;,
 4;195,193,197,199;,
 4;197,196,200,201;,
 4;196,198,202,200;,
 4;198,199,203,202;,
 4;199,197,201,203;,
 4;201,200,204,205;,
 4;200,202,206,204;,
 4;202,203,207,206;,
 4;203,201,205,207;,
 4;205,204,208,209;,
 4;204,206,210,208;,
 4;206,207,211,210;,
 4;207,205,209,211;,
 4;209,208,212,213;,
 4;208,210,214,212;,
 4;210,211,215,214;,
 4;211,209,213,215;,
 4;213,212,216,217;,
 4;212,214,218,216;,
 4;214,215,219,218;,
 4;215,213,217,219;,
 4;217,216,220,221;,
 4;216,218,222,220;,
 4;218,219,223,222;,
 4;219,217,221,223;,
 4;221,220,169,168;,
 4;220,222,172,169;,
 4;222,223,174,172;,
 4;223,221,168,174;,
 3;224,225,226;,
 3;224,226,227;,
 3;224,227,228;,
 3;224,228,229;,
 3;224,229,230;,
 3;224,230,231;,
 3;224,231,232;,
 3;224,232,225;,
 4;233,234,235,236;,
 4;233,236,227,226;,
 4;233,226,225,237;,
 4;233,237,238,234;,
 4;236,235,239,240;,
 4;236,240,228,227;,
 4;237,225,232,241;,
 4;237,241,242,238;,
 4;240,239,243,244;,
 4;240,244,229,228;,
 4;241,232,231,245;,
 4;241,245,246,242;,
 4;244,243,247,248;,
 4;244,248,230,229;,
 4;245,231,230,248;,
 4;245,248,247,246;,
 4;249,250,234,238;,
 3;251,250,249;,
 4;250,252,235,234;,
 3;251,252,250;,
 4;252,253,239,235;,
 3;251,253,252;,
 4;253,254,243,239;,
 3;251,254,253;,
 4;254,255,247,243;,
 3;251,255,254;,
 4;255,256,246,247;,
 3;251,256,255;,
 4;256,257,242,246;,
 3;251,257,256;,
 4;257,249,238,242;,
 3;251,249,257;,
 4;258,259,260,261;,
 4;259,262,263,260;,
 4;262,264,265,263;,
 4;264,258,261,265;,
 4;264,262,259,258;,
 4;261,260,263,265;,
 4;266,267,268,269;,
 4;267,270,271,268;,
 4;270,272,273,271;,
 4;272,266,269,273;,
 4;272,270,267,266;,
 4;269,268,271,273;,
 4;274,275,276,277;,
 4;275,278,279,276;,
 4;278,280,281,279;,
 4;280,274,277,281;,
 4;280,278,275,274;,
 4;277,276,279,281;,
 4;282,283,284,285;,
 4;283,286,287,284;,
 4;286,288,289,287;,
 4;288,282,285,289;,
 4;288,286,283,282;,
 4;285,284,287,289;,
 4;290,291,292,293;,
 4;291,294,295,292;,
 4;294,296,297,295;,
 4;296,290,293,297;,
 4;296,294,291,290;,
 4;293,292,295,297;,
 4;298,299,300,301;,
 4;299,302,303,300;,
 4;302,304,305,303;,
 4;304,298,301,305;,
 4;304,302,299,298;,
 4;301,300,303,305;,
 4;306,307,308,309;,
 4;307,310,311,308;,
 4;310,312,313,311;,
 4;312,306,309,313;,
 4;312,310,307,306;,
 4;309,308,311,313;,
 4;314,315,316,317;,
 4;315,318,319,316;,
 4;318,320,321,319;,
 4;320,314,317,321;,
 4;320,318,315,314;,
 4;317,316,319,321;,
 4;322,323,324,325;,
 4;325,324,326,327;,
 4;327,326,328,329;,
 4;329,328,323,322;,
 4;329,322,325,327;,
 4;323,328,326,324;,
 4;330,331,332,333;,
 4;333,332,334,335;,
 4;335,334,336,337;,
 4;337,336,331,330;,
 4;337,330,333,335;,
 4;331,336,334,332;,
 4;338,339,340,341;,
 4;341,340,342,343;,
 4;343,342,344,345;,
 4;345,344,339,338;,
 4;345,338,341,343;,
 4;339,344,342,340;,
 4;346,347,348,349;,
 4;349,348,350,351;,
 4;351,350,352,353;,
 4;353,352,347,346;,
 4;353,346,349,351;,
 4;347,352,350,348;,
 4;354,355,356,357;,
 4;357,356,358,359;,
 4;359,358,360,361;,
 4;361,360,355,354;,
 4;361,354,357,359;,
 4;355,360,358,356;,
 4;362,363,364,365;,
 4;365,364,366,367;,
 4;367,366,368,369;,
 4;369,368,363,362;,
 4;369,362,365,367;,
 4;363,368,366,364;,
 4;370,371,372,373;,
 4;373,372,374,375;,
 4;375,374,376,377;,
 4;377,376,371,370;,
 4;377,370,373,375;,
 4;371,376,374,372;,
 4;378,379,380,381;,
 4;381,380,382,383;,
 4;383,382,384,385;,
 4;385,384,379,378;,
 4;385,378,381,383;,
 4;379,384,382,380;,
 4;386,387,388,389;,
 4;387,390,391,388;,
 4;390,392,393,391;,
 4;392,386,389,393;,
 4;392,390,387,386;,
 4;389,388,391,393;,
 4;394,395,396,397;,
 4;395,398,399,396;,
 4;398,400,401,399;,
 4;400,394,397,401;,
 4;400,398,395,394;,
 4;397,396,399,401;,
 4;402,403,404,405;,
 4;403,406,407,404;,
 4;406,408,409,407;,
 4;408,402,405,409;,
 4;408,406,403,402;,
 4;405,404,407,409;,
 4;410,411,412,413;,
 4;411,414,415,412;,
 4;414,416,417,415;,
 4;416,410,413,417;,
 4;416,414,411,410;,
 4;413,412,415,417;;
 
 MeshMaterialList {
  1;
  384;
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
  0;;
  Material {
   0.517600;0.524000;0.228800;1.000000;;
   8.000000;
   0.300000;0.300000;0.300000;;
   0.000000;0.000000;0.000000;;
  }
 }
}