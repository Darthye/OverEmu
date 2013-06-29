#include "ScriptPCH.h"
 
#define GOSSIP_HEAL 1
#define GOSSIP_BUFF 2
 
#define BUFF_1 123
#define BUFF_2 342
#define BUFF_3 765
 
class BuffHealNPC : public CreatureScript
{
    public: BuffHealNPC() : CreatureScript("BuffHealNPC") { }
 
        bool OnGossipHello(Player* player, Creature* pCreature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Heal me for full HP", GOSSIP_SENDER_MAIN, GOSSIP_HEAL);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Buff me up", GOSSIP_SENDER_MAIN, GOSSIP_BUFF);
            player->PlayerTalkClass->SendGossipMenu(1, pCreature->GetGUID());
        return true;
        }
 
         void ReturnToMainMenu(Player* player, Creature* creature)
         {
            player->PlayerTalkClass->ClearMenus();
            OnGossipHello(player, creature);
         }
 
         char str[255];
 
        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
                player->PlayerTalkClass->ClearMenus();
 
                switch (uiAction)
                {
                        case GOSSIP_HEAL:
                                {
                                        SpellInfo const* spell = sSpellMgr->GetSpellInfo(2061);
 
                                        if(player->GetHealth() == player->GetMaxHealth())
                                        {
                                                sprintf(str, "You don't need any heal right now!");
                                        }
                                        else
                                        {
                                                player->HealBySpell(player, spell, player->GetMaxHealth(), false);
 
                                                sprintf(str, "You have been healed to your maxim health");
                                        }
 
                                        player->MonsterWhisper(str, player->GetGUID(), true);
 
                                        ReturnToMainMenu(player, creature);
                                        break;
                                }
                        case GOSSIP_BUFF:
                                {
                                        player->AddAura(BUFF_1, player);
                                        player->AddAura(BUFF_2, player);
                                        player->AddAura(BUFF_3, player);
 
                                        sprintf(str, "You have been buffed!");
 
                                        player->MonsterWhisper(str, player->GetGUID(), true);
 
                                        ReturnToMainMenu(player, creature);
                                        break;
                                }
 
                }
                return true;
         }
};
 
void AddSC_BuffHealNPC()
{
    new BuffHealNPC();
}