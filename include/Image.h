#include <vector>

#ifndef __IMAGE_H__
#define __IMAGE_H__

class Image {
public:
	int width;
	int height;
	std::vector<glm::vec3> pixels; // RGB colors;

	Image() {
		width = 0;
		height = 0;
		//pixels = 0;
		pixels.resize(0, glm::vec3(0.0));
	}


	Image(int w, int h) {
		width = w;
		height = h;
		pixels.resize(w * h, glm::vec3(0.0));
	};

	unsigned int fbo; // framebuffer object
	unsigned int tbo; // texture buffer object

	void init() {
		glGenFramebuffers(1, &fbo);
		glGenTextures(1, &tbo);
	}

	void draw() {
		glBindTexture(GL_TEXTURE_2D, tbo);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, // load texture
			0, GL_RGB, GL_FLOAT, &pixels[0][0]);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, tbo, 0);// attach texture and the read frame
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // if not already so
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT,
			GL_NEAREST); // copy framebuffer from read to write
	}
};
#endif

