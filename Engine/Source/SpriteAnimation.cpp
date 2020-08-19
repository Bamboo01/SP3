#include "SpriteAnimation.h"
#include <cstdarg>

//Constructor
SpriteAnimation::SpriteAnimation(const std::string& meshName, int row, int col)
	: Mesh(meshName)
	, row(row)
	, col(col)
	, currentTime(0)
	, currentFrame(0)
	, playCount(0)
	, currentAnimation("")
{
}

//Destructor
SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::Update(double dt)
{
	//Check if the current animation is active
	if (animationList[currentAnimation]->animActive)
	{
		//Add the delta time
		currentTime += static_cast<float>(dt);

		//Get the number of frame to get the frame per second
		int numFrame = animationList[currentAnimation]->frames.size();
		float frameTime = animationList[currentAnimation]->animTime / numFrame;

		//Set the current frame based on the current time
		currentFrame = animationList[currentAnimation]->frames[
			fmin((int)animationList[currentAnimation]->frames.size() - 1, 
			static_cast<int>(currentTime / frameTime))
		];

		//Check if the current time is more the total animated time
		if (currentTime >= animationList[currentAnimation]->animTime)
		{
			//if it is less than the repeat count, incease the count and repeat
			if (playCount < animationList[currentAnimation]->repeatCount)
			{
				++playCount;
				currentTime = 0;
				currentFrame = animationList[currentAnimation]->frames[0];
			}
			//if we repeat count is 0 or we have reach same number of play count
			else
			{
				animationList[currentAnimation]->animActive = false;
				animationList[currentAnimation]->ended = true;
			}
			//If the animation is infinite
			if (animationList[currentAnimation]->repeatCount == -1)
			{
				currentTime = 0.f;
				currentFrame = animationList[currentAnimation]->frames[0];
				animationList[currentAnimation]->animActive = true;
				animationList[currentAnimation]->ended = false;
			}

		}
	}
}

void SpriteAnimation::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));


	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if (mode == DRAW_LINES)
	{
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(currentFrame * 6 * sizeof(GLuint)));
	}
	else if (mode == DRAW_TRIANGLE_STRIP)
	{
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(currentFrame * 6 * sizeof(GLuint)));
	}
	else
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(currentFrame * 6 * sizeof(GLuint)));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

//Add an animation to the Sprite Animation by defining the start and the end
//param anim_name - the name of the animation
//param start - the starting frame based on the sprite sheet
//param end - the ending frame based on the sprite sheet
void SpriteAnimation::AddAnimation(std::string anim_name, int start, int end)
{
	Animation* anim = new Animation();
	//Check if start is more than end
	//Swap over if it is
	if (start > end)
		std::swap(start, end);
	//Add in all the frames in the range
	for (int i = start; i < end; ++i)
	{
		anim->AddFrame(i);
	}
	//Link the animation to the animation list
	animationList[anim_name] = anim;
	//Set the current animation if it does not exisit
	if (currentAnimation == "")
	{
		currentAnimation = anim_name;
	}
	animationList[anim_name]->animActive = false;
}

//Add an animation to the Sprite Animation by defining the frame values
 //param anim_name - the name of the animation
 //param count - the number of frame in the animation
 //param ... - the frames
void SpriteAnimation::AddSequeneAnimation(std::string anim_name, int count ...)
{
	Animation* anim = new Animation();
	va_list args;
	va_start(args, count);
	//Add the frames based on the input
	for (int i = 0; i < count; ++i)
	{
		int value = va_arg(args, int);
		anim->AddFrame(value);
	}
	va_end(args);
	//Link the animation to the animation list
	animationList[anim_name] = anim;
	//Set the current animation if it does not exisit
	if (currentAnimation == "")
	{
		currentAnimation = anim_name;
	}
	animationList[anim_name]->animActive = false;
}

//Play the animation based on the given name
//param anim_name - the name of the animation
//param repeat - the number of repeats (-1 for infinite looping)
//param time - the total time of the animation
void SpriteAnimation::PlayAnimation(std::string anim_name, int repeat, float time)
{
	//Check if the anim name exist
	if (animationList[anim_name] != nullptr)
	{
		currentAnimation = anim_name;
		animationList[anim_name]->Set(repeat, time, true);
	}
}

//Resume the current animation
void SpriteAnimation::Resume()
{
	animationList[currentAnimation]->animActive = true;
}
//Pause the current animation
void SpriteAnimation::Pause()
{
	animationList[currentAnimation]->animActive = false;
}
//Reset the current animation
void SpriteAnimation::Reset()
{
	currentFrame = animationList[currentAnimation]->frames[0];
	playCount = 0;
}