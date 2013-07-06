local Color1 = color(Var "Color1");
local Color2 = color(Var "Color2");

local t = Def.ActorFrame {};

t[#t+1] = LoadActor(Var "File1") .. {
	OnCommand=function(self)
		self:diffuse(Color1);
		self:blend("BlendMode_Add");
		self:x(SCREEN_CENTER_X);
		self:y(SCREEN_CENTER_Y);
		self:scale_or_crop_background();
		self:linear(1);
		self:diffusealpha(0);
	end;
	GainFocusCommand=function(self)
		self:play();
	end;
	LoseFocusCommand=function(self)
		self:pause();
	end;
};

return t;
