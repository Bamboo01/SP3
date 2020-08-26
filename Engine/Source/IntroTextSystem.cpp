#include "IntroTextSystem.h"
#include "GUIText.h"

void IntroTextSystem::Init()
{
	timer = 0;
	count = 0;
}

void IntroTextSystem::Update(float dt)
{
	timer += 0.5f * dt;

	if (timer > 0 && count == 0)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("computer rebooting...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if(timer > 0.8 && count == 1)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.25, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 00G%SK001", ALIGN_LEFT,glm::vec3(1,0,0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 1 && count == 2)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.15, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 0$UIS%07^", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 1.3 && count == 3)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.05, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Resources...0%", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 2 && count == 4)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.95, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Resources...63%", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 2.7 && count == 5)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.85, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Re$o%r&es... 100%", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 3 && count == 6)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.75, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 7&*UYA_0E", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 3.5 && count == 7)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.65, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Comp&e^t(d...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 3.8 && count == 8)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.55, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("ProCe$$inG...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 4 && count == 9)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.45, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 8^DJ000E", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 4.5 && count == 10)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("R%b00t su(e$$fu1ly...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 4.8 && count == 11)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.25, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> installing ##082##", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5 && count == 12)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.15, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> installing ##793##", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.5 && count == 13)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.05, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> &#0&*AQ0", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.55 && count == 14)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.05, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> 56&*^PQ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.6 && count == 15)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.15, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> *&&&SjeAWpA90*72D$#59eDo_0294D8173", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.65 && count == 16)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.25, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> 78d9U*e&6%2AQ0(ajOsieESp;lsnENuBVI*&2 ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.7 && count == 17)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> OUir**7sHAuw^5%%ed98eJUQ- ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.75 && count == 18)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.45, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 8Podu*371Gew5S^$%ene(88", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.8 && count == 19)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.55, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> UTI*7420mKFJe_01949", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.85 && count == 20)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.65, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> PO0(0E82HDBNOQ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.9 && count == 21)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.75, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> UTIW&*207572OBFkF9)*726", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5.95 && count == 22)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.85, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> IPHET92^)927460*", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6 && count == 23)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.95, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> PIEU(*4)(72igbK;JFEW8&&2", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.05 && count == 24)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.05, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> O[9073^*3957", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.1 && count == 25)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.15, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> IPMFA*7&5%18^^", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.15 && count == 26)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.25, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> IRHGB90&&&&6111*BWih:}[d", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.2 && count == 27)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 8ST7()&sBjkfbOAU&&*%^2NWL", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.25 && count == 28)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> lpo%%$$SKpoalfo*0^&769bouugF", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.3 && count == 29)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> LDOPEuio*f&97(^d9BLASFN", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<VIRUS DETECTED> PG0(UHE6&&&vwlKNF###2df%", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.35 && count == 30)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> P_DPA8097BfhblF&&6%s1", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.4 && count == 31)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> {F-W9hBiyrBiyf&&*1@!kSLpo", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<VIRUS DETECTED> _f0jnFOgQ8)IUHF%3#$%6(^T3GBIFKJ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.45 && count == 32)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> PlFOPn208527Blkf'FE;'.<.SQU39", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.5 && count == 33)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> PPLFOBW9726()&842YHOljbf*^7;pkfn", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<VIRUS DETECTED> SIKGHB8*(&FRT6$#$%762YBlbfS", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.55 && count == 34)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> *DBNobG&%29(f0lFOPHW^(872Bjbf", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 6.6 && count == 35)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> P[DV{}SPIKXB*^516.>I176", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<ERROR> OHBF(&Q^9287rTGVBFeLOjfOUWB*^)2", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.65 && count == 36)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> IUJNfk()&26*&046lPISD&*@&E6", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<VIRUS DETECTED> L:FN8wyirhsf-(&42846_ierth0q86UOBJF", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.7 && count == 37)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> pIUHBV092740B_(*&61LK><nf", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<VIRUS DETECTED> [sUFJHWUOE)&(8265T0GpklbF[PKWR[OPGB", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.8 && count == 38)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> pIUHBV092740B_(*&61LK><nf", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<ERROR> P[DG*836579%()92U4JHklsbFL", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.85 && count == 39)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> P:shfB0A8WYRGBFOlj.ZD94WTI", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<ERROR> opHFKXG9286W4975q60975ytqgobaulj", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.9 && count == 40)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> JLGB0(&@)*46T3uoLSBFo$$@$#287WIURGBFK ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<VIRUS DETECTED> PAIDHG08365807yshfljbnp;wrpiyq357", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 6.95 && count == 41)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> PIF97*^@&($564198yiHBRFKJJIF ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		ScrollUpdate();
		Entity UIText2 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText2, Transform());
		coordinator.GetComponent<Transform>(UIText2).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText2).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText2, CanvasText("<VIRUS DETECTED> piyfgbouv&(w$578Q&&5387_25-(yr", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText2, EntityState());
		++count;
	}
	else if (timer > 7.2 && count == 42)
	{
		ScrollUpdate();
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("L0adi*g Com[#eted ", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 7.7 && count == 43)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			auto& state = coordinator.GetComponent<EntityState>(a);
			state.active = false;
		}
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.5f, 0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("_", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
		//blinking = true;
	}
	else if (timer > 7.9 && count == 44)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "W_";
		}
		++count;
	}
	else if (timer > 8.0 && count == 45)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WE_";
		}
		++count;
	}
	else if (timer > 8.1 && count == 46)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WEL_";
		}
		++count;
	}
	else if (timer > 8.2 && count == 47)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC_";
		}
		++count;
	}
	else if (timer > 8.3 && count == 48)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0_";
		}
		++count;
	}
	else if (timer > 8.4 && count == 49)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0M_";
		}
		++count;
	}
	else if (timer > 8.5 && count == 50)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME_";
		}
		++count;
	}
	else if (timer > 8.6 && count == 51)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME _";
		}
		++count;
	}
	else if (timer > 8.7 && count == 52)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME T_";
		}
		++count;
	}

	else if (timer > 8.8 && count == 53)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO_";
		}
		++count;
	}
	else if (timer > 8.9 && count == 54)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO _";
		}
		++count;
	}
	else if (timer > 9 && count == 55)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H_";
		}
		++count;
	}
	else if (timer > 9.1 && count == 56)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0_";
		}
		++count;
	}
	else if (timer > 9.2 && count == 57)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L_";
		}
		++count;
	}
	else if (timer > 9.3 && count == 58)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0_";
		}
		++count;
	}

	else if (timer > 9.4 && count == 59)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0W_";
		}
		++count;
	}

	else if (timer > 9.5 && count == 60)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0WA_";
		}
		++count;
	}

	else if (timer > 9.6 && count == 61)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0WAR_";
		}
		++count;
	}

	else if (timer > 9.7 && count == 62)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0WAR._";
		}
		++count;
	}

	else if (timer > 9.8 && count == 63)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0WAR.E_";
		}
		++count;
	}

	else if (timer > 9.9 && count == 64)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0WAR.EX_";
		}
		++count;
	}

	else if (timer > 10 && count == 65)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			text.Text = "WELC0ME TO H0L0WAR.EXE_";
		}
		++count;
	}
	else if (timer > 10.35 && count == 66)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.5f;
		}
		++count;
	}
	else if (timer > 10.45 && count == 67)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.56f;
		}
		++count;
	}
	else if (timer > 10.46 && count == 68)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.5f;
		}
		++count;
	}
	else if (timer > 10.48 && count == 69)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.44f;
		}
		++count;
	}
	else if (timer > 10.5 && count == 70)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.5f;
		}
		++count;
	}
	else if (timer > 10.52 && count == 71)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.54f;
		}
		++count;
	}
	else if (timer > 10.54 && count == 72)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.5f;
		}
		++count;
	}
	else if (timer > 10.56 && count == 73)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.46f;
		}
		++count;
	}
	else if (timer > 10.58 && count == 74)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			scroll.position.x = -0.5f;
		}
		++count;
	}
	else if (timer > 10.65)
	{
		for (auto& a : m_Entities)
		{
			auto& scroll = coordinator.GetComponent<Transform>(a);
			auto& text = coordinator.GetComponent<CanvasText>(a);
			if (text.color != glm::vec3(0, 0, 0))
			{
				text.color.r -= 0.01f;
				text.color.g -= 0.01f;
				text.color.b -= 0.01f;
			}
		}
	}
}

void IntroTextSystem::ScrollUpdate()
{
	for (auto& a : m_Entities)
	{
		auto& scroll = coordinator.GetComponent<Transform>(a);
		auto& text = coordinator.GetComponent<CanvasText>(a);

		scroll.position.y += 0.1;
	}
}
