return NOTESKIN:LoadActor("DownRight","Tap Note")..{
	InitCommand=function(self)
		self:effectclock("beat");
		self:effectmagnitude(0.5, 1, 0);
	end;
};