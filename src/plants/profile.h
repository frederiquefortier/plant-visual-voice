struct PlantProfile {
  const char* name;
  MoistureThreshold threshold;
  const uint16_t* overwaterImage;
  const uint16_t* perfectImage;
  const uint16_t* thirstyImage;
  const uint16_t* dyingImage;
};
