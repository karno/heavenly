# heavenly make-file

CC		= gcc
CXX		= g++

FLAGS	= 

OBJS	= heavenly.o Tile.o PlayerMachine.o CriteriaSystem.o \
		  AllGreen.o \
		  AllHonors.o \
		  AllSimples.o \
		  AllTerminals.o \
		  AllTerminalsHonors.o \
		  AllTriples.o \
		  BigDragons.o \
		  ConcealedFour.o \
		  ConcealedThree.o \
		  ConcealedTsumo.o \
		  DoubleRiichi.o \
		  DoubleRun.o \
		  DoubleRuns.o \
		  EarthlyHand.o \
		  Evaluator.o \
		  FinalTileWin.o \
		  FirstRound.o \
		  FourQuads.o \
		  FourWinds.o \
		  FullFlush.o \
		  FullStraight.o \
		  HalfFlush.o \
		  HeavenlyHand.o \
		  KingsTile.o \
		  LittleDragons.o \
		  MixedOutsides.o \
		  NineGates.o \
		  Peace.o \
		  PureOutsides.o \
		  Riichi.o \
		  RobbingQuad.o \
		  SevenPairs.o \
		  ThirteenOrphans.o \
		  ThreeColorRuns.o \
		  ThreeColorTriples.o \
		  ThreeQuads.o \
		  UserPlayer.o \
		  Values.o \
		  Winds.o \
		  TileFactory.o \
		  TileSystem.o \
		  GameSystem.o \
		  Player.o

heavenly.exe : $(OBJS)
	$(CXX) -o $(FLAGS) $@	$(OBJS)


.c.o:
	$(CC) -c $(FLAGS) $<


clean:
	rm -f *.o
	rm -f heavenly.exe



