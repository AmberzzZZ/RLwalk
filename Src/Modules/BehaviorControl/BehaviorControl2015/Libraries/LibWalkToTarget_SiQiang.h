 /**
  * @class LibWalkToTarget
  * @author ZhouZQ
  * @date 1/03/2017
  * @file LibWalkToTarget.h
  * @brief
  */

/**
 * @TODO

  *
  *
  *
  *
  * */

#pragma once

class LibWalkToTarget : public LibraryBase
{
 public:
	LibWalkToTarget();

  void preProcess() override;
  void postProcess() override;
//  float kxMembership[7][3] = {
//		 {0.330f, 0.386f,  0.330f},		//-3
//		 {0.500f, 0.500f,  0.386f},		//-2
//		 {0.670f, 0.500f,  0.330f},		//-1
//		 {0.670f, 0.500f,  0.500f},		//0
//		 {0.670f, 0.614f,  0.670f},		//1
//		 {0.500f, 0.500f,  0.500f},		//2
//		 {0.330f, 0.386f,  0.330f},		//3
// };
//  float kyMembership[3][4] = {
//		 {0.400f, 0.400f,  0.105f, 0.075f},		//0
//		 {0.651f, 0.651f,  0.120f, 0.120f},		//1
//		 {1.000f, 0.955f,  0.105f, 0.075f},		//1
// };
//  float kthetagammaMembership[4] = {
//		 1.000f, 0.040f,  0.040f, 1.000f	//0
// };
//  float kthetaphiMembership[4] = {
//		 0.f, 0.96f,  0.96f, 0.f		//0
// };
  float kxMembership[7][3] = {
		 {0.000f, 0.250f,  0.000f},		//-3
		 {0.500f, 0.500f,  0.250f},		//-2
		 {1.000f, 0.500f,  0.000f},		//-1
		 {1.000f, 0.500f,  0.500f},		//0
		 {1.000f, 0.750f,  1.000f},		//1
		 {0.500f, 0.500f,  0.500f},		//2
		 {0.250f, 0.250f,  0.000f},		//3
 };
  float kyMembership[3][4] = {
		 {0.392f, 0.338f,  0.183f, 0.128f},		//0
		 {0.625f, 0.558f,  0.388f, 0.159f},		//1
		 {0.754f, 0.655f,  0.333f, 0.137f},		//1
 };
  float kthetagammaMembership[4] = {
		 0.670, 0.339f,  0.339f, 0.670f	//0
 };
  float kthetaphiMembership[4] = {
		 0.330f, 0.661f,  0.661f, 0.330f		//0
 };
  float alphaValue;		//robot-target angle
  float gammaValue;		//robot-ball angle
  float phiValue;		//robot-ball-target complementary angle
  float betaValue;		//robot-target-ball angle
  float rhoValue;		//robot-ball distance
  float psiValue;		//ball-target distance
  //just use for judge state
//  float alpha;
//  float gamma;
//  float phi;
//  float beta;
//  float rho;
//  float psi;

//  float kxValue;
  Vector2f target;
//  Vector2f assignTarget;//(4100.f,0.f)
  Vector2f goal;
//  SemanticFourStates BlurTheGamma();
  void GetParameter();
  void GetAllParameterValue(float &kx,float &ky,float &kthetagamma, float &kthetaphivalue,Vector2f &target_1,Vector2f &assignTarget_1);
  float GetKxValue();
  float GetKyValue();
  float GetKthetagammaValue();
  float GetKthetaphiValue();

  int GetGammaSemanticValue();
  int GetPhiSemanticValue();
  int GetRhoSemanticValue();
//  void GetKxSemanticValue();
};
