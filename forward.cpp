void
Forward( float th1, float th2, float th3,  float l1, float l2,
	 glm::mat4& m1g, glm::mat4& m2g, glm::mat4& m3g )
{

	glm::mat4 Identity;
	glm::mat4 tl1 = glm::translate(Identity, glm::vec3(0.,0.,0.));
	glm::mat4 tl2 = glm::translate(Identity, glm::vec3(l1,0.,0.));
	glm::mat4 tl3 = glm::translate(Identity, glm::vec3(l2,0.,0.));
	glm::mat4 r1 = glm::rotate(Identity, th1, glm::vec3(0.,0.,1.));
	glm::mat4 r2 = glm::rotate(Identity, th2, glm::vec3(0.,0.,1.));
	glm::mat4 r3 = glm::rotate(Identity, th3, glm::vec3(0.,0.,1.));
	// glm::mat4 x21 = glm::mat4();
	// glm::mat4 x32 = glm::mat4();

	th1 *= (M_PI / 180.);
	th2 *= (M_PI / 180.);
	th3 *= (M_PI / 180.);

	x1g = tl1 * r1;
	x2g = x1g * tl2 * r2;
	x3g = tl1 * r1 * tl2 * r2 * tl3 * r3;

}

void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
        yourName = "Grace Bullock";
        yourEmailAddress = "bullocgr@oregonstate.edu" ;
}