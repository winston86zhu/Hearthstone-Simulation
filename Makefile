CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD 
EXEC = sorcery
OBJECTS = main.o Canvas.o Player.o CardCollection.o DeckCollection.o GroundCollection.o ascii_graphics.o\
			Card.o AbsMinion.o Minion.o Spell.o Ritual.o Enchantment.o Ability.o \
			Banish.o Unsummon.o Recharge.o Disenchant.o RaiseDead.o Blizzard.o \
			Airelemental.o Earthelemental.o BoneGolem.o FireElemental.o PotionSeller.o NovicePyromancer.o ApprenticeSummoner.o MasterSummoner.o\
			Giantstrength.o Enrage.o Haste.o MagicFatigue.o Silence.o Customized.o\
			DarkRitual.o AuraOfPower.o Standstill.o Nuke.o
DEPENDS = ${OBJECTS:.o=.d}
# replace ".o" in OBJECTS with .d

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}
# how does it know to find .cc file? just the same name?

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
