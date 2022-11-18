/*
 * This program completes the necessary tasks for the second programming assignment.
 * Various comments on the functionalities of the different functions (Hadoop and Java).
 *
 * See COSC420 repository for more information...
*/
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.ArrayList;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class socialNetwork {
    public static class NodeMapper extends Mapper<Object,Text,Text,Text>{
        public void map(Object obj,Text friends,Context context)throws IOException, InterruptedException{
            String[] list = friends.toString().split(" ",0);
            for (int i=1;i<list.length;i++){
                context.write(new Text(list[0]), new Text(list[i]));
            }
        }
    }

    public static class PairMapper extends Mapper<Object,Text,IntWritable,IntWritable>{
        public void map(Object key, Text friends,Context context)throws IOException, InterruptedException{
            String[] list = friends.toString().split(" ",0);
            String[] pairs = new String[2];
            for(int i=1; i<list.length;i++){
                for(int j=i+1;i<list.length-1;j++){
                    if (list[i].equals(list[j])==false){
                        String pair = list[i] + " " + list[j];
                        pairs[0] = list[0] + " " + list[i];
                        pairs[1] = list[0] + " " + list[j];
                        context.write(new Text(pair),new Text(pairs[0] + " " + pairs[1]));
                    }
                }
            }
        }
    }

    public static class TripletReducer extends Reducer<IntWritable,IntWritable,IntWritable,IntWritable>{
        public void reduce(IntWritable key,IntWritable value,Context context)throws IOException, InterruptedException{
            context.write(key,value);
        }
    }

    public static void main(String[] args)throws Exception{
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "social network");
        job.setJarByClass(socialNetwork.class);
        job.setMapperClass(PairMapper.class);
        job.setReducerClass(TripletReducer.class);
        job.setOutputKeyClass(IntWritable.class);
        job.setOutputValueClass(IntWritable.class);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
