

// This sketch is designed as a POC for a Simple Genetic Algorithm to find PID gain values

// In Arduino, we need to be aware of memory usage, and can't just have a bunch of dynamically sized arrays floating around
// So, we have a Population Array that is always full (size p), and a to-be-evaluated array (size q) that is always full
// We generate a full population, sort by fitness metric, then replace the last q elements with the to-be-evaluated array before sorting again

const int population_init = 6;  // necessary for algorithm to decide how many to init for first generation
const int population_cap = 6;  // population_cap
const float effective_range = 10; // how close does the current need to be to the target in order to succeed

// for simulation purposes, these are targets for our sga to reach
const float p_target = 5;
const float i_target = 8;
const float d_target = 7;
const float metric_target = p_target * i_target * d_target; 

// genome data type
// every genome will pretty much always have pid gains, from propagation to culling
// does this data type need any class methods or inheritance? (pretty sure no)

struct genome{
  float p_gain; 
  float i_gain;
  float d_gain;
  float performance_metric; // this can be null when the genome first appears and will be set after evaluation

};

genome g = {12, 4, 3};

int cmpfunc(genome& a, genome& b) {
  return a.performance_metric < b.performance_metric;
}

void setup() {



  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  g.performance_metric = 69.420;

  #ifdef DEBUG
  Serial.print("Metric target: ");
  Serial.print(metric_target);
  Serial.print(", Current Metric: ");
  Serial.println(g.performance_metric);
  #endif
  
  // init first generation

  genome population[population_cap];

  for (int i=0; i<population_init; i++) {

    // logic for randomly spinning up first generation

    int this_p = random(100);
    int this_i = random(100);
    int this_d = random(100);

    genome this_genome = {this_p, this_i, this_d};

    population[i] = this_genome;
  }

  // time to start evaluating the population

  int population_size = sizeof(population) / sizeof(population[0]);

  for (int i=0; i<population_size; i++) {
    // evaluation function, set the fitness metric for an evaluated individual

    // for this demo, we're just setting the performance metric to the multiplication of these 3 values
    population[i].performance_metric = population[i].p_gain * population[i].i_gain * population[i].d_gain;
    
    #ifdef DEBUG
    // verify value exists by printing
    Serial.println(population[i].performance_metric);
    #endif
  
  }
  
  qsort(population, population_size, sizeof(genome), cmpfunc);

  for (int i=0;i<population_size;i++) {
    Serial.println(population[i].performance_metric);
    delay(1000);
  }





}
