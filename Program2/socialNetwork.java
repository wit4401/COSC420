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
    public static class MapperOne extends Mapper<Object,Text,Text,Text>{
        public void map(Object obj,Text friends,Context context)throws IOException, InterruptedException{
            String[] list = friends.toString().split(" ",0);
            for (int i=1;i<list.length;i++){
                if(list[0]<list[i])
                    context.write(new Text(list[0]), new Text(list[i]));
            }
        }
    }

    public static class MapperTwo extends Mapper<Object,Text,Text,Text>{
        public void map(Object key, Text friends,Context context)throws IOException, InterruptedException{

        }
    }

    public static class ReducerOne extends Reducer<Text,Text,Text,Text>{
        public void reduce(Text key,Text value,Context context)throws IOException, InterruptedException{
            
        }
    }

    public static class ReducerTwo extends Reducer<Text,Text,Text,Text>{
        public void reduce(Text key,Text value,Context context)throws IOException, InterruptedException{
            
        }
    }

    public static void main(String[] args)throws Exception{
        Configuration conf = new Configuration();

        Job job1 = Job.getInstance(conf, "social network1");
        
        job1.setJarByClass(socialNetwork.class);
        job1.setMapperClass(MapperOne.class);
        job1.setReducerClass(ReducerOne.class);
        job1.setOutputKeyClass(Text.class);
        job1.setOutputValueClass(Text.class);
        FileInputFormat.addInputPath(job1, new Path(args[0]));
        FileOutputFormat.setOutputPath(job1, new Path(args[1]));

        Job job2 = Job.getInstance(conf, "social network2");
        job2.setJarByClass(socialNetwork.class);
        job2.setMapperClass(MapperTwo.class);
        job2.setReducerClass(ReducerTwo.class);
        job2.setOutputKeyClass(Text.class);
        job2.setOutputValueClass(Text.class);
        FileInputFormat.addInputPath(job2, new Path(args[0]));
        FileOutputFormat.setOutputPath(job2, new Path(args[1]));
        
        System.exit(job1.waitForCompletion(true) ? 0 : 1);
        System.exit(job2.waitForCompletion(true) ? 0 : 1);

    }
}
