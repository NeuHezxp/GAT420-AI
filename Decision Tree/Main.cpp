
#include "Node.h"
// traverse root using recursion
void traverse(node_t* node)
{
	// Base case: if the current node is null, we've reached the end of a branch
	if (node == nullptr) {
		return;
	}

	node_t* nextNode = node->execute();
	if (nextNode != nullptr) {
		traverse(nextNode); // Call traverse with next node
	}
}
int main(int argc, char* argv[])
{
	float xp = 20;
	float health = 40;
	bool tired = false;
	int npcFavorability = 60;

	node_t* fightAction = new action_t("fight");
	node_t* restAction = new action_t("rest");
	node_t* helpNPCAction = new action_t("Help NPC");
	node_t* ignoreNPCAction = new action_t("Ignore NPC");
	

	node_t* root = new decision_t<float>("xp", xp, ePredicate::Greater, 10);
	node_t* combatDecision = new decision_t<float>("Health", health, ePredicate::Less, 50);
	node_t* restDecision = new decision_t<bool>("tired", tired, ePredicate::Equal, false);
	node_t* npcDecision = new decision_t<int>("NPC attitude", npcFavorability, ePredicate::Greater, 50);

	//	root (XP check)
	//	    /    \
	//   Combat    \
	// Decision    \
	//    /    \    \
	//  Rest   Fight \
	//         /     \
	//        /       NPC decision
	//       /        /             \
	//      /     Help NPC         Ignore NPC

	root->trueNode = combatDecision; // If XP > 10, check combat decision
	root->falseNode = fightAction; // If XP <= 10, go fight

	combatDecision->trueNode = restAction; // If health < 50, rest
	combatDecision->falseNode = npcDecision; // If health >= 50, fight

	npcDecision->trueNode = helpNPCAction; // If NPC favorability > 50
	npcDecision->falseNode = ignoreNPCAction; // If NPC favorability <= 50

	restDecision->trueNode = restAction; // If tired, rest
	restDecision->falseNode = fightAction; // If not tired, fight





	// traverse decision tree from root
	traverse(root);
}
